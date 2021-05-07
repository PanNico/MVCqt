#include "../include/mvcqtModel.h"
#include <QDebug>

MVCqtModel::MVCqtModel(QObject *parent) :
    QObject(parent),
    running(false)
{
    qDebug() << "MVCqtModel created";
}

MVCqtModel::~MVCqtModel()
{
    qDebug() << "MVCqtModel destroied";
    if(running)
        endModel();
}

void MVCqtModel::controller_channel_rx(QString cmd)
{
    qDebug() << "MVCqtModel received message " << cmd << " from MVCqtController";

    if( cmd == "start" ){
        startModel();
    }
    else if( cmd == "end" ){
        endModel();
    }
    else{
        qDebug() << "MVCqtModel received unknown message " << cmd << " from MVCqtController";
    }
}

void MVCqtModel::startModel()
{
    qDebug() << "MVCqtModel started";
    running=true;
}

void MVCqtModel::endModel()
{
    qDebug() << "MVCqtModel ended";
    running=false;
}
