/*
* MIT License
* Copyright (c) 2021 Nicola Pancheri
* pancheri.nicola@gmail.com
*/

#include "../include/mvcqtController.h"
#include <MVCqt/MVCqtView/mvcqtView.h>
#include <MVCqt/MVCqtModel/mvcqtModel.h>

MVCqtController::MVCqtController(MVCqtModel* _backend, const int _window_width, const int _window_height, QObject *parent) :
    QObject(parent),
    model(_backend),
    view(new MVCqtView(_window_width, _window_height, this))
{
#ifdef MVC_QT_DEBUG
    print_str("MVCqtController created");
#endif
}

MVCqtController::~MVCqtController()
{

#ifdef MVC_QT_DEBUG
    print_str("MVCqtController destroyed");
#endif
}


void MVCqtController::defaultConnections()
{
#ifdef MVC_QT_DEBUG
    print_str("MVCqtController creating default connections..");
#endif

    connect(this, &MVCqtController::model_channel_tx, model.data(), &MVCqtActor::controller_channel_rx );
    connect(model.data(), &MVCqtActor::controller_channel_tx, this, &MVCqtController::model_channel_rx );
    connect(this, &MVCqtController::view_channel_tx, view.data(), &MVCqtActor::controller_channel_rx );
    connect(view.data(), &MVCqtActor::controller_channel_tx, this, &MVCqtController::view_channel_rx );
    connect((MVCqtModel*)model.data(), &MVCqtModel::view_channel_tx, (MVCqtView*)view.data(), &MVCqtView::model_channel_rx );
    connect((MVCqtView*)view.data(), &MVCqtView::model_channel_tx, (MVCqtModel*)model.data(), &MVCqtModel::view_channel_rx );


   // connections();
}

void MVCqtController::start()
{
#ifdef MVC_QT_DEBUG
    print_str("MVCqtController started");
#endif

    defaultConnections();
    emit model_channel_tx("start");
    emit view_channel_tx("start");

#ifdef MVC_QT_DEBUG
    emit model_channel_tx("hello");
    emit view_channel_tx("hello");
#endif
}

void MVCqtController::model_channel_rx(const QString cmd)
{
#ifdef MVC_QT_DEBUG
    std::ostringstream ss;
    ss << "MVCqtController received message " << cmd.toStdString() << " from MVCqtModel";
    print_str(ss);
#endif
}

void MVCqtController::view_channel_rx(const QString cmd)
{
#ifdef MVC_QT_DEBUG
    std::ostringstream ss;
    ss << "MVCqtController received message " << cmd.toStdString() << " from MVCqtView";
    print_str(ss);
#endif

    if( cmd == "stop" ){
        emit model_channel_tx("stop");
        emit view_channel_tx("stop");
        emit stopQAppl();
    }

}
