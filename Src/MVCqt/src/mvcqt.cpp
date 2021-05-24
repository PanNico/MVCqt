/*
* MIT License
* Copyright (c) 2021 Nicola Pancheri
* pancheri.nicola@gmail.com
*/

#include "../include/mvcqt.h"
#include <QtWebEngine>
#include <QFile>
#include <QJsonDocument>

static int argc=1;
static char* application_name[1];
//static QString conffilename("app_settings.conf");

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

void validateConfFile(QJsonDocument& json_conf, MVCqt* _this)
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

        _this->config=new MVCqt::MVCqtConf(name, window_height.toInt(), window_width.toInt(), false);
    }
    else{
        _this->config=new MVCqt::MVCqtConf(name, 0, 0, true);
    }
}

void readConfFile(MVCqt* _this)
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

MVCqt::MVCqt(MVCqtModel* _backend, QObject *parent) :
    QObject(parent),
    config(nullptr)
{
#ifdef MVC_QT_DEBUG
    print_str("MVCqt Framework Constructor");
#endif
    readConfFile(this);

    QByteArray tmp=config->appName.toLocal8Bit();
    application_name[0]=tmp.data();

    QtWebEngine::initialize();
    appl=new QApplication(argc, application_name);

    controller = new MVCqtController(_backend, config->windowWidth, config->windowHeight);

    connect(controller, &MVCqtController::stopQAppl, this, &MVCqt::stopQAppl );
}

MVCqt::~MVCqt()
{
#ifdef MVC_QT_DEBUG
    print_str("Ending MVCqt Framework...");
#endif
    delete config;
    delete controller;
    delete appl;
#ifdef MVC_QT_DEBUG
    print_str("MVCqt Framework ended.");
#endif
}

void MVCqt::start()
{
#ifdef MVC_QT_DEBUG
    print_str("MVCqt Framework start...");
#endif
    controller->start();
    appl->exec();
#ifdef MVC_QT_DEBUG
    print_str("MVCqt Framework exit from start.");
#endif
}

void MVCqt::stopQAppl()
{
#ifdef MVC_QT_DEBUG
    print_str("Closing MVCqt Framework...");
#endif
    appl->quit();
}
