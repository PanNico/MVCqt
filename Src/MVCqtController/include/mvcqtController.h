/*
* MIT License
* Copyright (c) 2021 Nicola Pancheri
* pancheri.nicola@gmail.com
*/

#ifndef MVCQTCONTROLLER_H
#define MVCQTCONTROLLER_H

#include <QApplication>
#include <QThread>
#include <QSharedPointer>
#include <MVCqt/MVCqtView/mvcqtView.h>
#include <MVCqt/MVCqtModel/mvcqtModel.h>
#include <unordered_map>

template <class CustomModel>
class MVCqtController;

/*
 * Allows to connect the model and view with signals and slots
 */
class MVCqtQController : public QObject {
    Q_OBJECT

    public:
        explicit MVCqtQController(const int _window_width, const int _window_height,
                                    MVCqtActor* model, QApplication* _qapp);
        ~MVCqtQController();
        std::string start();

    private slots:
        void model_channel_rx(const QString cmd);
        void view_channel_rx(const QString cmd);
        void view_rx_rpc(const QString cmd);

    private:
        MVCqtActor* model;
        MVCqtActor* view;
        QApplication* qapp;
        void defaultConnections();

    signals:
        void model_channel_tx(const QString cmd);
        void view_channel_tx(const QString cmd);

};

template <class CustomModel>
class MVCqtController
{

    public:
        typedef void (CustomModel::*ModelMethod)();

        explicit MVCqtController(QApplication* _qapp, CustomModel* _backend, const int _window_width, const int _window_height):
            model(_backend),
            qController(_window_width, _window_height, static_cast<MVCqtModel*>(_backend), _qapp),
            stop(true)
        {
        #ifdef MVC_QT_DEBUG
            print_str("MVCqtController created");
        #endif
        }

        ~MVCqtController()
        {
            stop=true;
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

            qController.start();

        }

        bool callModelRpc(std::string method_name)
        {
            auto iter=names_to_methods.find(method_name);
            CustomModel& mod_ref=*model.data();
            ModelMethod metod=iter->second;

            (mod_ref.*metod)();

            return !(iter == names_to_methods.end());
        }


        void registerModelRpc(std::string method_name, ModelMethod method)
        {
            names_to_methods.insert(std::make_pair(method_name,method));
        }

    private:
        std::unordered_map<std::string,ModelMethod> names_to_methods;
        QSharedPointer<CustomModel> model;
        MVCqtQController qController;
        bool stop;


};

#endif // MVCQTCONTROLLER_H
