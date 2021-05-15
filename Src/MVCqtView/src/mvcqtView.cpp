#include "../include/mvcqtView.h"

MVCqtView::MVCqtView(QObject *parent) :
    MVCqtActor(parent)
{
#ifdef MVC_QT_DEBUG
    print_str("MVCqtView created");
#endif
}

MVCqtView::~MVCqtView()
{
#ifdef MVC_QT_DEBUG
    print_str("MVCqtView destroyed");
#endif
}

void MVCqtView::actorStart()
{
#ifdef MVC_QT_DEBUG
    print_str("MVCqtView started");
    emit model_channel_tx("hello");
#endif
}

void MVCqtView::actorStop()
{
#ifdef MVC_QT_DEBUG
    print_str("MVCqtView ended");
#endif
}

bool MVCqtView::cmds_controller_channel(const QString cmd)  // must return true if the comand has been recognized else false
{
#ifdef MVC_QT_DEBUG
    std::ostringstream ss;
    ss << "MVCqtView received message " << cmd.toStdString() << " from MVCqtController";
    print_str(ss);
#endif
#ifdef MVC_QT_DEBUG
    if(cmd == "hello"){
        print_str("MVCqtView parsed correctly hello message.");
        emit controller_channel_tx("hello");
        return true;
    }
#endif

    return false;
}

void MVCqtView::model_channel_rx(const QString cmd)
{
#ifdef MVC_QT_DEBUG
    std::ostringstream ss;
    ss << "MVCqtView received message " << cmd.toStdString() << " from MVCqtModel";
    print_str(ss);
#endif
}

