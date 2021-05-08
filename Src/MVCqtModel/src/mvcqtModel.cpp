#include "../include/mvcqtModel.h"

MVCqtModel::MVCqtModel(QObject *parent) :
    MVCqtActor(parent)
{
    #ifdef MVC_QT_DEBUG
        print_str("MVCqtModel created");
    #endif
}

MVCqtModel::~MVCqtModel()
{
    #ifdef MVC_QT_DEBUG
        print_str("MVCqtModel destroied");
    #endif
}

void MVCqtModel::controller_channel_rx(QString cmd)
{

#ifdef MVC_QT_DEBUG
    std::ostringstream ss;
    ss << "MVCqtModel received message " << cmd.toStdString() << " from MVCqtController";
    print_str(ss);
#endif

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
