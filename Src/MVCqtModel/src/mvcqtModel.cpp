/*
* MIT License
* Copyright (c) 2021 Nicola Pancheri
* pancheri.nicola@gmail.com
*/

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
    print_str("MVCqtModel destroyed");
#endif
}

void MVCqtModel::actorStart()
{
#ifdef MVC_QT_DEBUG
    print_str("MVCqtModel started");
#endif
}

void MVCqtModel::actorStop()
{
#ifdef MVC_QT_DEBUG
    print_str("MVCqtModel ended");
#endif
}

bool MVCqtModel::cmds_controller_channel(const QString cmd)  // must return true if the comand has been recognized else false
{
#ifdef MVC_QT_DEBUG
    std::ostringstream ss;
    ss << "MVCqtModel received message " << cmd.toStdString() << " from MVCqtController";
    print_str(ss);
#endif
#ifdef MVC_QT_DEBUG
    if(cmd == "hello"){
        print_str("MVCqtModel parsed correctly hello message.");
        emit controller_channel_tx("hello");
        return true;
    }
#endif

    return false;
}

const QString queryToJsonStr(QString& msg_name, QVector<QString>& fields )
{
    QString header="{\""+msg_name+"\":[";
    QString tail="]}";
    QString body="";

    for( QString& str : fields ) body+="\""+str+"\",";
    body.remove(body.size()-1,1);
    return header+body+tail;
}

QVector<QString> MVCqtModel::query_ui_fields(QString msg_name, QVector<QString> fields)
{
    emit view_channel_tx(queryToJsonStr(msg_name,fields));
    return query_register->read(msg_name);
}
