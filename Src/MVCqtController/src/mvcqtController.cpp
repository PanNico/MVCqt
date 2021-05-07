#include "../include/mvcqtController.h"
#include <QDebug>
#include <iostream>

using namespace std;

MVCqtController::MVCqtController(QObject *parent) :
    QObject(parent),
    model(new MVCqtModel(this))
{

    qDebug() << "MVCqtController created";
    cout << "guarda qua" << endl;
}

MVCqtController::~MVCqtController()
{
    qDebug() << "MVCqtController destroied";
}


void MVCqtController::defaultConnections()
{
    connect(this, &MVCqtController::model_channel_tx, (MVCqtModel*)model.data(), &MVCqtModel::controller_channel_rx);
    connect((MVCqtModel*)model.data(), &MVCqtModel::controller_channel_tx, this, &MVCqtController::model_channel_rx);
    connections();
}

void MVCqtController::start()
{
    qDebug() << "MVCqtController started";
    defaultConnections();
    emit model_channel_tx("start");

}

void MVCqtController::model_channel_rx(QString cmd)
{
    qDebug() << "MVCqtController received message " << cmd << " from MVCqtModel";
}
