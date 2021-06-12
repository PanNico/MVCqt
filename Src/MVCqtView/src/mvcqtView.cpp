/*
* MIT License
* Copyright (c) 2021 Nicola Pancheri
* pancheri.nicola@gmail.com
*/

#include "../include/mvcqtView.h"
#include <QGuiApplication>
#include <QScreen>

MVCqtView::MVCqtView(const int _width, const int _height, QObject *parent) :
    MVCqtActor(parent),
    html_window(new QWebEngineView()),
    html_dir(":/frontend/"),
    width(_width),
    height(_height)
{

    QRect screenGeom=QGuiApplication::primaryScreen()->geometry();

    html_window->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    html_window->setGeometry(screenGeom.width()/2-width/2, screenGeom.height()/2-height/2, width, height);
    html_window->setFixedSize(width, height);

    connect(html_window, &QWebEngineView::urlChanged, this, &MVCqtView::urlChanged );
    connect(html_window, &QWebEngineView::loadStarted, this, &MVCqtView::loadStarted );

#ifdef MVC_QT_DEBUG
    print_str("MVCqtView created");
#endif
}

MVCqtView::~MVCqtView()
{
#ifdef MVC_QT_DEBUG
    print_str("MVCqtView called destructor");
#endif
    html_window->stop();
    html_window->close();

    delete html_window;

#ifdef MVC_QT_DEBUG
    print_str("MVCqtView destroyed");
#endif
}

void MVCqtView::actorStart()
{
#ifdef MVC_QT_DEBUG
    print_str("MVCqtView started");
#endif

    html_window->load(QUrl("qrc:/frontend/index.html"));
    html_window->show();

}

void MVCqtView::actorStop()
{
#ifdef MVC_QT_DEBUG
    print_str("MVCqtView ended");
#endif
}

bool MVCqtView::cmds_controller_channel(const QString cmd)  // must return true if the comand has been recognized else false
{
#ifdef MVC_QT_DEBUG
    std::ostringstream ss;
    ss << "MVCqtView received message " << cmd.toStdString() << " from MVCqtController";
    print_str(ss);
#endif
#ifdef MVC_QT_DEBUG
    if(cmd == "hello"){
        print_str("MVCqtView parsed correctly hello message.");
        emit controller_channel_tx("hello");
        return true;
    }
#endif

    return false;
}

void MVCqtView::model_channel_rx(const QString cmd)
{
#ifdef MVC_QT_DEBUG
    std::ostringstream ss;
    ss << "MVCqtView received message " << cmd.toStdString() << " from MVCqtModel";
    print_str(ss);
#endif
}

void MVCqtView::urlChanged(const QUrl &url)
{
    QString str_url(url.toString());
#ifdef MVC_QT_DEBUG
    if(str_url.indexOf('#') >= 0){
        std::ostringstream ss;
        ss << "MVCqtView received from UI message: " << str_url.mid(str_url.indexOf("#")+1).toStdString();
        print_str(ss);
    }
#endif

    if(str_url.indexOf('#') >= 0){
        QString msg=str_url.mid(str_url.indexOf("#")+1);
        QString recipient=msg.left(msg.indexOf("_"));
        QString command=msg.mid(msg.indexOf("_")+1);

#ifdef MVC_QT_DEBUG
        print_str("Message for: "+recipient.toStdString());
        print_str("Command: "+command.toStdString());
#endif
        if(recipient == "controller"){
            emit controller_channel_tx(command);
        }
        else if(recipient == "model"){
            emit model_channel_tx(command);
        }

    }

}

void MVCqtView::loadStarted()
{
#ifdef MVC_QT_DEBUG
    std::ostringstream ss;
    ss << "MVCqtView: UI has started load a new page...";
    print_str(ss);
#endif

}
