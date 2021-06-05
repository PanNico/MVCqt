/*
* MIT License
* Copyright (c) 2021 Nicola Pancheri
* pancheri.nicola@gmail.com
*/
#include "../include/mvcqtQController.h"
#include <MVCqt/MVCqtView/mvcqtView.h>
#include <MVCqt/MVCqtModel/mvcqtModel.h>

static bool initialized=false;

MVCqtQController::MVCqtQController(std::shared_ptr<MVCqtActor> _model,  MVCqtActor* _view, std::shared_ptr<QApplication> _qapp, RpcsChannel& _rpcs_channel ) :
    QObject(nullptr),
    model(_model),
    view(_view),
    qapp(_qapp),
    rpcs_channel(_rpcs_channel)
{
    model->moveToThread(&modelThread);

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

void MVCqtQController::start()
{
#ifdef MVC_QT_DEBUG
    print_str("MVCqtQController started");
#endif
    if(!initialized){
        defaultConnections();
        modelThread.start();
        emit model_channel_tx("start");
        emit view_channel_tx("start");
#ifdef MVC_QT_DEBUG
    emit model_channel_tx("hello");
    emit view_channel_tx("hello");
#endif
        initialized=true;
    }

}

void MVCqtQController::model_channel_rx(const QString cmd)
{
#ifdef MVC_QT_DEBUG
    std::ostringstream ss;
    ss << "MVCqtQController received message " << cmd.toStdString() << " from MVCqtModel";
    print_str(ss);
#endif
}

void MVCqtQController::view_channel_rx(const QString cmd)
{
#ifdef MVC_QT_DEBUG
    std::ostringstream ss;
    ss << "MVCqtQController received message " << cmd.toStdString() << " from MVCqtView";
    print_str(ss);
#endif

    if( cmd == "stop" ){
        emit model_channel_tx("stop");
        emit view_channel_tx("stop");

        modelThread.quit();
        modelThread.wait();
        qapp->quit();
    }

}

void MVCqtQController::view_rx_rpc(const QString cmd)
{
#ifdef MVC_QT_DEBUG
    std::ostringstream ss;
    ss << "MVCqtQController received rpc " << cmd.toStdString() << " from MVCqtView";
    print_str(ss);
#endif

    rpcs_channel.writeRpc(cmd.toStdString());
}

void MVCqtQController::defaultConnections()
{
#ifdef MVC_QT_DEBUG
    print_str("MVCqtQController creating default connections..");
#endif
    connect(&modelThread, &QThread::finished, model.get(), &QObject::deleteLater, Qt::QueuedConnection);

    connect(this, &MVCqtQController::model_channel_tx, model.get(), &MVCqtActor::controller_channel_rx, Qt::QueuedConnection );
    connect(model.get(), &MVCqtActor::controller_channel_tx, this, &MVCqtQController::model_channel_rx, Qt::QueuedConnection );
    connect(this, &MVCqtQController::view_channel_tx, view.get(), &MVCqtActor::controller_channel_rx, Qt::QueuedConnection );
    connect(view.get(), &MVCqtActor::controller_channel_tx, this, &MVCqtQController::view_channel_rx, Qt::QueuedConnection );
    connect(static_cast<MVCqtModel*>(model.get()), &MVCqtModel::view_channel_tx, static_cast<MVCqtView*>(view.get()), &MVCqtView::model_channel_rx, Qt::QueuedConnection );
    connect(static_cast<MVCqtView*>(view.get()), &MVCqtView::model_channel_tx, this, &MVCqtQController::view_rx_rpc, Qt::QueuedConnection );

}

