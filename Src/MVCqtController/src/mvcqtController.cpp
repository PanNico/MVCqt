#include "../include/mvcqtController.h"
#include <iostream>

using namespace std;

MVCqtController::MVCqtController(QObject *parent) :
    QObject(parent),
    model(new MVCqtModel(this))
{

    cout << "MVCqtController created" << endl;

}

MVCqtController::~MVCqtController()
{
    cout << "MVCqtController destroied" << endl;
}


void MVCqtController::defaultConnections()
{
    connect(this, &MVCqtController::model_channel_tx, (MVCqtModel*)model.data(), &MVCqtModel::controller_channel_rx);
    connect((MVCqtModel*)model.data(), &MVCqtModel::controller_channel_tx, this, &MVCqtController::model_channel_rx);
    connections();
}

void MVCqtController::start()
{
    cout << "MVCqtController started" << endl;
    defaultConnections();
    emit model_channel_tx("start");
    emit model_channel_tx("hello");

}

void MVCqtController::model_channel_rx(QString cmd)
{
    cout << "MVCqtController received message " << cmd.toStdString() << " from MVCqtModel" << endl;
}
