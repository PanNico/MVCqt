/*
* MIT License
* Copyright (c) 2021 Nicola Pancheri
* pancheri.nicola@gmail.com
*/

#ifndef MVCQTCONTROLLER_H
#define MVCQTCONTROLLER_H

#include <QApplication>
#include <QThread>
#include <chrono>
#include <thread>
#include <memory>
#include <QSharedPointer>
#include <QMutex>
#include <QWaitCondition>
#include <MVCqt/MVCqtView/mvcqtView.h>
#include <MVCqt/MVCqtModel/mvcqtModel.h>
#include <unordered_map>
/*
 * MVCqtController is the controller following the MVC design pattern. It keeps the instances of the model and the view
 * and allows them to comunicate.
 * As you can see in the code below do exist MVCqtController and MVCqtQController: the former is the templatic interface of the
 * controller the latter keeps the instances of model and view and connect them with signals and slots;
 * I need MVCqtController because a QObject can't be templatic;
 * The MVCqtController's controller takes as input every kind of object that extends MVCqtModel and the end user has to register
 * the association name used in the view and method of the object passed to the constructor through the use
 *  of  registerModelRpc(std::string method_name, ModelMethod method.
 *  MVCqtController and MVCqtQController share a their own thread.
 *
 *  SPIEGA COME AVVIENE LA COMUNICAZIONE
 */
template <class CustomModel>
class MVCqtController;

class RpcsChannel{
    public:
        RpcsChannel() :
            stop(false),
            received_rpc(false),
            rpc_string("")
            {}

        void writeRpc(std::string msg){
            do{
                variable_guard.lock();
                if(!received_rpc){               
                    rpc_string=msg;
                    received_rpc=true;
                    variable_guard.unlock();
                    readable.wakeAll();                  
                    return;
                }
                variable_guard.unlock();
                writeable.wait(&rpcs_mutex);
                stop_guard.lock();
                    if(stop){
                        rpc_string="";
                        received_rpc=false;
                        stop_guard.unlock();
                        return;
                    }
                stop_guard.unlock();
            }while(true);


        }

        std::string readRpc(){
            do{
                variable_guard.lock();
                if(received_rpc){
                    std::string toRet = rpc_string;
                    rpc_string="";
                    received_rpc=false; 
                    variable_guard.unlock();
                    writeable.wakeAll();
                    return toRet;
                }
                variable_guard.unlock();
                readable.wait(&rpcs_mutex);
                stop_guard.lock();
                    if(stop){
                        rpc_string="";
                        received_rpc=false;
                        stop_guard.unlock();
                        return "";
                    }
                stop_guard.unlock();

            }
            while(true);

        }

        void close_channel(){
            stop_guard.lock();
            stop=true;
            readable.wakeAll();
            writeable.wakeAll();
            stop_guard.unlock();
        }

    private:
        bool stop;
        bool received_rpc=false;
        std::string rpc_string="";
        QMutex rpcs_mutex;
        QMutex variable_guard;
        QMutex stop_guard;
        QWaitCondition readable;
        QWaitCondition writeable;


};

/*
 * Allows to connect the model and view with signals and slots
 */
class MVCqtQController : public QObject {
    Q_OBJECT

    public:
        explicit MVCqtQController(MVCqtActor* _model, MVCqtActor* _view, QApplication* _qapp, RpcsChannel* _rpcs_channel);
        ~MVCqtQController();

    public slots:
        void start();

    private slots:
        void model_channel_rx(const QString cmd);
        void view_channel_rx(const QString cmd);
        void view_rx_rpc(const QString cmd);

    private:
        MVCqtActor* model;
        QThread modelThread;
        MVCqtActor* view;
        QApplication* qapp;
        RpcsChannel* rpcs_channel;
        void defaultConnections();

    signals:
        void model_channel_tx(const QString cmd);
        void view_channel_tx(const QString cmd);

};

template <class CustomModel>
void rpc_listener(MVCqtController<CustomModel>* ctrl, void (MVCqtController<CustomModel>::*ControllerMethod)() )
{
    (ctrl->*ControllerMethod)();
}

template <class CustomModel>
class MVCqtController
{

    public:
        typedef void (CustomModel::*ModelMethod)();

        explicit MVCqtController(QApplication* _qapp, CustomModel* _backend, const int _window_width, const int _window_height):
            model(_backend),
            qController(static_cast<MVCqtModel*>(_backend), new MVCqtView(_window_width, _window_height), _qapp, &rpcs_channel),
            stop(true)
        {
            qController.moveToThread(&qCtrlThread);
            QObject::connect(&qCtrlThread, &QThread::finished, &qController, &QObject::deleteLater, Qt::QueuedConnection);
            QObject::connect(&qCtrlThread, &QThread::started, &qController, &MVCqtQController::start, Qt::QueuedConnection);

        #ifdef MVC_QT_DEBUG
            print_str("MVCqtController created");
        #endif
        }

        ~MVCqtController()
        {
            stop=true;
            rpcs_channel.close_channel();
            qCtrlThread.quit();
            qCtrlThread.wait();
            rpcs_listener_thread->join();
        #ifdef MVC_QT_DEBUG
            print_str("MVCqtController destroyed");
        #endif
        }

        void start()
        {
            stop=false;
        #ifdef MVC_QT_DEBUG
            print_str("MVCqtController started");
        #endif


            rpcs_listener_thread=std::unique_ptr<std::thread>(new std::thread(rpc_listener<CustomModel>, this, &MVCqtController<CustomModel>::rpcs_listener));
            qCtrlThread.start();

        }

        void rpcs_listener()
        {
        #ifdef MVC_QT_DEBUG
            print_str("MVCqtController rpcs listener started.");
        #endif
            while(!stop){

                std::string cmd=rpcs_channel.readRpc();

        #ifdef MVC_QT_DEBUG
            std::ostringstream ss;
            ss << "MVCqtController received rpc " << cmd;
            print_str(ss);
        #endif
                auto iter=names_to_methods.find(cmd);

                if(iter != names_to_methods.end()){
                    CustomModel& mod_ref=*model.data();
                    ModelMethod metod=iter->second;

                #ifdef MVC_QT_DEBUG
                    print_str("MVCqtController running rpc...");
                #endif
                    (mod_ref.*metod)();
                #ifdef MVC_QT_DEBUG
                    print_str("MVCqtController rpc executed!");
                #endif
                }
                else{
                #ifdef MVC_QT_DEBUG
                    print_str("MVCqtController warning: rpc not found");
                    print_str("MVCqtController registered rpcs:");

                    for(auto ptr=names_to_methods.begin(); ptr != names_to_methods.end(); ptr++)
                        print_str(ptr->first);
                #endif
                }

            }

        #ifdef MVC_QT_DEBUG
            print_str("MVCqtController rpcs listener stopped.");
        #endif
        }


        void registerModelRpc(std::string method_name, ModelMethod method)
        {
            names_to_methods.insert(std::make_pair(method_name,method));
        }

    private:
        std::unordered_map<std::string,ModelMethod> names_to_methods;
        QSharedPointer<CustomModel> model;
        MVCqtQController qController;
        RpcsChannel rpcs_channel;
        QThread qCtrlThread;
        std::unique_ptr<std::thread> rpcs_listener_thread;
        bool stop;


};

#endif // MVCQTCONTROLLER_H
