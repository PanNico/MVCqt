#include "../include/mvcqtActor.h"

using namespace std;

void startActor(MVCqtActor* actor)
{
#ifdef MVC_QT_DEBUG
    print_str("MVCqtActor started");
#endif

    actor->actorStart(); // fai diventate startActor friend...
    running=true;
}


MVCqtActor::MVCqtActor(QObject *parent) :
    QObject(parent),
    running(false)
{
    register_cmd("start", &this->startActor);
    register_cmd("end", &this->endActor);
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


void MVCqtActor::endActor()
{
#ifdef MVC_QT_DEBUG
    print_str("MVCqtActor ended");
#endif

    actorStop();
    running=false;
}

void MVCqtActor::register_cmd(const QString cmd, void (*cmdFunc)()){
#ifdef MVC_QT_DEBUG
    print_str("MVCqtActor ended");
#endif
    command_list.append(make_pair(cmd, cmdFunc));
}

void MVCqtActor::controller_channel_rx(QString cmd)
{
#ifdef MVC_QT_DEBUG
    print_str("MVCqtActor controller_channel_rx");
#endif

    bool found=false;

    for(auto& cmd_registered : command_list){
        if( cmd == cmd_registered.first ){
           (*cmd_registered.second)();
            found=true;
            break;
        }
    }

    if(!found)
        emit controller_channel_tx("Command not found");
}
