#include "../include/mvcqtActor.h"

QVector<QString> UiQueriesRegister::read(QString query_name)
{

    auto src_result=queries_results.find(query_name);

    while(src_result == queries_results.end()){
        ready_to_read.wait(&queries_mutex, QDeadlineTimer(100));
        src_result=queries_results.find(query_name);
    }

    return src_result->second;

}

void UiQueriesRegister::write(QString query_name, QVector<QString> result)
{
    queries_results[query_name]=result;
    ready_to_read.wakeAll();
}

MVCqtActor::MVCqtActor(QObject *parent) :
    QObject(parent),
    query_register(nullptr),
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
    print_str("MVCqtActor destroyed");
#endif
}

void MVCqtActor::setQueryRegister(UiQueriesRegister* _query_register)
{
    query_register=_query_register;
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
    else if(cmd == "stop"){
        endActor();
        found = true;
    }
    else
        found = cmds_controller_channel(cmd);


    if(!found)
        emit controller_channel_tx("Command not found");
}
