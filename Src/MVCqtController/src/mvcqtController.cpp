/*
* MIT License
* Copyright (c) 2021 Nicola Pancheri
* pancheri.nicola@gmail.com
*/
#include "../include/mvcqtController.h"

static bool received_rpc=false;
static std::string rpc_string="";
static bool initialized=false;

static std::string read_rpc(){
    received_rpc =false;
    return rpc_string;
}

static void write_rpc(std::string method_name){
    rpc_string=method_name;
    received_rpc =true;
}

MVCqtQController::MVCqtQController(const int _window_width, const int _window_height,
                                    MVCqtActor* model, QApplication* _qapp ) :
    QObject(nullptr),
    model(model),
    view(new MVCqtView(_window_width, _window_height, this)),
    qapp(_qapp)
{
#ifdef MVC_QT_DEBUG
    print_str("MVCqtQController created");
#endif
}

MVCqtQController::~MVCqtQController()
{
#ifdef MVC_QT_DEBUG
    print_str("MVCqtQController destroyed");
#endif
}

std::string MVCqtQController::start()
{
#ifdef MVC_QT_DEBUG
    print_str("MVCqtQController started");
#endif
    if(!initialized){
        defaultConnections();
        emit model_channel_tx("start");
        emit view_channel_tx("start");
#ifdef MVC_QT_DEBUG
    emit model_channel_tx("hello");
    emit view_channel_tx("hello");
#endif
        initialized=true;
    }


    return read_rpc();
}

void MVCqtQController::model_channel_rx(const QString cmd)
{
#ifdef MVC_QT_DEBUG
    std::ostringstream ss;
    ss << "MVCqtController received message " << cmd.toStdString() << " from MVCqtModel";
    print_str(ss);
#endif
}

void MVCqtQController::view_channel_rx(const QString cmd)
{
#ifdef MVC_QT_DEBUG
    std::ostringstream ss;
    ss << "MVCqtController received message " << cmd.toStdString() << " from MVCqtView";
    print_str(ss);
#endif

    if( cmd == "stop" ){
        emit model_channel_tx("stop");
        emit view_channel_tx("stop");
        delete view;
        qapp->quit();
    }

}

void MVCqtQController::view_rx_rpc(const QString cmd)
{
#ifdef MVC_QT_DEBUG
    std::ostringstream ss;
    ss << "MVCqtController received rpc " << cmd.toStdString() << " from MVCqtView";
    print_str(ss);
#endif

    write_rpc(cmd.toStdString());
}

void MVCqtQController::defaultConnections()
{
#ifdef MVC_QT_DEBUG
    print_str("MVCqtController creating default connections..");
#endif

    connect(this, &MVCqtQController::model_channel_tx, model, &MVCqtActor::controller_channel_rx );
    connect(model, &MVCqtActor::controller_channel_tx, this, &MVCqtQController::model_channel_rx );
    connect(this, &MVCqtQController::view_channel_tx, view, &MVCqtActor::controller_channel_rx );
    connect(view, &MVCqtActor::controller_channel_tx, this, &MVCqtQController::view_channel_rx );
    connect(static_cast<MVCqtModel*>(model), &MVCqtModel::view_channel_tx, static_cast<MVCqtView*>(view), &MVCqtView::model_channel_rx );
    connect(static_cast<MVCqtView*>(view), &MVCqtView::model_channel_tx, this, &MVCqtQController::view_rx_rpc );

}

