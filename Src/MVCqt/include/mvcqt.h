/*
* MIT License
* Copyright (c) 2021 Nicola Pancheri
* pancheri.nicola@gmail.com
*/

#ifndef MVCQT_H
#define MVCQT_H

#include <MVCqt/MVCqtController/mvcqtController.h>
#include <MVCqt/MVCqtModel/mvcqtModel.h>
#include <QApplication>
#include <QtWebEngine>
#include <QFile>
#include <QJsonDocument>

class ConfNotFoundException : public QException
{
    public:
        void raise() const override { throw *this; }
        ConfNotFoundException *clone() const override { return new ConfNotFoundException(*this); }
};

class NoJsonConfException : public QException
{
    public:
        void raise() const override { throw *this; }
        NoJsonConfException *clone() const override { return new NoJsonConfException(*this); }
};

class InvalidConfException : public QException
{
    public:
        void raise() const override { throw *this; }
        InvalidConfException *clone() const override { return new InvalidConfException(*this); }
};

class MissingConfFieldException : public QException
{
    public:
        void raise() const override { throw *this; }
        MissingConfFieldException *clone() const override { return new MissingConfFieldException(*this); }
};

class InvalidConfFieldException : public QException
{
    public:
        void raise() const override { throw *this; }
        InvalidConfFieldException *clone() const override { return new InvalidConfFieldException(*this); }
};

static int argc=1;
static char* application_name[1];

template <class CustomModel>
class MVCqt
{
    public:
        typedef void (CustomModel::*ModelMethod)();

        explicit MVCqt(CustomModel* _backend) :
            config(nullptr)
        {
        #ifdef MVC_QT_DEBUG
            print_str("MVCqt Framework Constructor");
        #endif
            readConfFile(this);

            QByteArray tmp = config->appName.toLocal8Bit();
            application_name[0] = tmp.data();

            QtWebEngine::initialize();
            appl = std::shared_ptr<QApplication>(new QApplication(argc, application_name));

            controller = std::unique_ptr<MVCqtController<CustomModel>>(new MVCqtController<CustomModel>(appl, _backend, config->windowWidth, config->windowHeight));

        }

        ~MVCqt()
        {

        #ifdef MVC_QT_DEBUG
            print_str("MVCqt Framework ended.");
        #endif
        }

        void start()
        {
        #ifdef MVC_QT_DEBUG
            print_str("MVCqt Framework start...");
        #endif
            controller->start();
        #ifdef MVC_QT_DEBUG
            print_str("MVCqt Framework starting QApplication...");
        #endif
            appl->exec();
        #ifdef MVC_QT_DEBUG
            print_str("MVCqt Framework exit from start.");
        #endif
        }

        void registerModelRpc(std::string method_name, ModelMethod method)
        {
            controller->registerModelRpc(method_name, method);
        }

    private:
        class MVCqtConf{
            public:
                MVCqtConf(QString& _appName, int _windowHeight, int _windowWidth, bool _fullscreen) :
                    appName(_appName),
                    windowHeight(_windowHeight),
                    windowWidth(_windowWidth),
                    fullscreen(_fullscreen)
                {}

                QString appName;
                int windowHeight;
                int windowWidth;
                bool fullscreen;
        };

        std::unique_ptr<MVCqtConf> config;
        std::unique_ptr<MVCqtController<CustomModel>> controller;
        std::shared_ptr<QApplication> appl;


        static void validateConfFile(QJsonDocument& json_conf, MVCqt* _this)
        {
        #ifdef MVC_QT_DEBUG
            print_str("MVCqt Framework validating json config...");
        #endif

            if(json_conf.isNull())
                throw NoJsonConfException();

            if(!json_conf.isObject())
                throw InvalidConfException();

            QJsonObject conf=json_conf.object();

            QJsonValue appName=conf.value("AppName");
            QJsonValue appWindow=conf.value("AppWindow");

            if( appName == QJsonValue::Undefined ||
                   appWindow == QJsonValue::Undefined  ){
                throw MissingConfFieldException();
            }

            if( !appName.isString() || !appWindow.isObject()  ){
                throw InvalidConfFieldException();
            }

            QJsonObject window_settings=appWindow.toObject();

            QJsonValue window_full=window_settings.value("fullscreen");
            QJsonValue window_height=window_settings.value("height");
            QJsonValue window_width=window_settings.value("width");
            QString name=appName.toString();

            if( window_full.isUndefined() ){
                if( !window_height.isDouble() || !window_width.isDouble() )
                    throw InvalidConfFieldException();

                _this->config=std::unique_ptr<MVCqtConf>(new MVCqt::MVCqtConf(name, window_height.toInt(), window_width.toInt(), false));
            }
            else{
                _this->config=std::unique_ptr<MVCqtConf>(new MVCqt::MVCqtConf(name, 0, 0, true));
            }
        }


        static void readConfFile(MVCqt* _this)
        {
        #ifdef MVC_QT_DEBUG
            print_str("MVCqt Framework reading conf file...");
        #endif
            QFile confFile(":/app_settings.conf");
            if(!confFile.open(QIODevice::ReadOnly))
                throw ConfNotFoundException();

            QByteArray fileBytes=confFile.readAll();
            confFile.close();

            QJsonDocument json_conf=QJsonDocument::fromJson(fileBytes);

            validateConfFile(json_conf, _this);

        }
};


#endif // MVCQT_H
