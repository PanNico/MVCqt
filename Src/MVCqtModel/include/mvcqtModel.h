/*
* MIT License
* Copyright (c) 2021 Nicola Pancheri
* pancheri.nicola@gmail.com
*/

#ifndef MVCQTMODEL_H
#define MVCQTMODEL_H

#include <MVCqt/MVCqtActor/mvcqtActor.h>


class MVCqtModel : public MVCqtActor
{
    Q_OBJECT

    public:
       MVCqtModel(QObject *parent = nullptr);
       ~MVCqtModel();

       virtual void run() = 0;

       /*
        * This function is used to retrives the value of the fields of the DOM.
        * You can do it also manually using "emit view_channel_tx(json_request)" where
        * json_request == {"msg_name":["field1", ... ,"fieldn"]}
        */
       void query_ui_fields(QString msg_name, QVector<QString> fields);

    private:
       void actorStart() override;
       void actorStop() override;
       bool cmds_controller_channel(const QString cmd) override; // must return true if the comand has been recognized else false

    signals:
       void view_channel_tx(const QString cmd);

};

#endif // MVCQTMODEL_H
