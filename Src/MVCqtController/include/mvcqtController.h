/*
* MIT License
* Copyright (c) 2021 Nicola Pancheri
* pancheri.nicola@gmail.com
*/

#ifndef MVCQTCONTROLLER_H
#define MVCQTCONTROLLER_H

#include "mvcqtQController.h"
#include "rpcsListener.h"
#include <thread>
#include <memory>
#include <MVCqt/MVCqtView/mvcqtView.h>

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
class MVCqtController
{

    public:
        typedef void (CustomModel::*ModelMethod)();

        explicit MVCqtController(std::shared_ptr<QApplication> _qapp, CustomModel* _backend, const int _window_width, const int _window_height):
            model(_backend),
            qController(model, new MVCqtView(_window_width, _window_height), _qapp, rpcs_channel),
            rpcs_listener(rpcs_channel, model, names_to_methods)
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
        #ifdef MVC_QT_DEBUG
            print_str("MVCqtController called destructor");
        #endif
            //here the order is important!
            rpcs_channel.close_channel();
            qCtrlThread.quit();
            rpcs_listener.stopListener();
            rpcs_listener_thread->join();
            qCtrlThread.wait();

        #ifdef MVC_QT_DEBUG
            print_str("MVCqtController destroyed");
        #endif
        }

        void start()
        {

        #ifdef MVC_QT_DEBUG
            print_str("MVCqtController started");
        #endif


            rpcs_listener_thread=std::unique_ptr<std::thread>(new std::thread(std::ref(rpcs_listener)));
            qCtrlThread.start();

        }

        void registerModelRpc(std::string method_name, ModelMethod method)
        {
            names_to_methods.insert(std::make_pair(method_name,method));
        }

    private:
        RpcsChannel rpcs_channel;
        std::unordered_map<std::string,ModelMethod> names_to_methods;
        std::shared_ptr<CustomModel> model;
        MVCqtQController qController;
        RpcsListener<CustomModel> rpcs_listener;
        QThread qCtrlThread;
        std::unique_ptr<std::thread> rpcs_listener_thread;




};

#endif // MVCQTCONTROLLER_H
