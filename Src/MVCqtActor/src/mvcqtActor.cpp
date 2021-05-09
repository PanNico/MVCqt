#include "../include/mvcqtActor.h"

using namespace std;

MVCqtActor::MVCqtActor(QObject *parent) :
    QObject(parent),
    running(false)
{
#ifdef MVC_QT_DEBUG
    print_str("MVCqtActor created");
#endif
}

MVCqtActor::~MVCqtActor()
{
    if(running)
        endActor();

#ifdef MVC_QT_DEBUG
    print_str("MVCqtActor created");
#endif
}

void MVCqtActor::startActor()
{
#ifdef MVC_QT_DEBUG
    print_str("MVCqtActor started");
#endif

    actorStart(); // fai diventate startActor friend...
    running=true;
}


void MVCqtActor::endActor()
{
#ifdef MVC_QT_DEBUG
    print_str("MVCqtActor ended");
#endif

    actorStop();
    running=false;
}

void MVCqtActor::controller_channel_rx(QString cmd)
{
#ifdef MVC_QT_DEBUG
    print_str("MVCqtActor controller_channel_rx");
#endif

    bool found=false;

    if(cmd == "start"){
        startActor();
        found = true;
    }
    else if(cmd == "end"){
        endActor();
        found = true;
    }
    else
        found = cmds_controller_channel(cmd);

    if(!found)
        emit controller_channel_tx("Command not found");
}
