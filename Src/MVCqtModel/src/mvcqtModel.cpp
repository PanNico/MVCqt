#include "../include/mvcqtModel.h"
#include <iostream>
using namespace std;

MVCqtModel::MVCqtModel(QObject *parent) :
    QObject(parent),
    running(false)
{
    cout << "MVCqtModel created" << endl;
}

MVCqtModel::~MVCqtModel()
{
    cout << "MVCqtModel destroied" << endl;
    if(running)
        endModel();
}

void MVCqtModel::controller_channel_rx(QString cmd)
{
    cout << "MVCqtModel received message " << cmd.toStdString() << " from MVCqtController" << endl;

    if( cmd == "start" ){
        startModel();
    }
    else if( cmd == "end" ){
        endModel();
    }
    else{
        cout << "MVCqtModel received unknown message " << cmd.toStdString() << " from MVCqtController" << endl;
    }
}

void MVCqtModel::startModel()
{
    cout << "MVCqtModel started" << endl;
    running=true;
}

void MVCqtModel::endModel()
{
    cout << "MVCqtModel ended" << endl;
    running=false;
}
