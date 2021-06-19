/*
* MIT License
* Copyright (c) 2021 Nicola Pancheri
* pancheri.nicola@gmail.com
*/

#ifndef MVCQTACTOR_H
#define MVCQTACTOR_H

#include <QObject>
#include <QString>
#include "mvcqtDebug.h"
#include <unordered_map>
#include <QWaitCondition>
#include <QMutex>

/*
 * Class used by the Model to read the fields of the DOM queried and by the View to insert the results of the queries and
 * notify that it has done to the Model.
 * This object is owned by every actor and bt the MVCqtQController but it is instantiated only by the MVCqtQController.
 */
class UiQueriesRegister{
    public:
        UiQueriesRegister();

        QVector<QString> read(QString query_name);
        void write(QString query_name, QVector<QString> result);

    private:
        QMutex queries_mutex;
        QWaitCondition ready_to_read;
        std::unordered_map<QString, QVector<QString>> queries_results;
};

class MVCqtActor : public QObject
{
    Q_OBJECT

    public:
        explicit MVCqtActor(QObject *parent = nullptr);
        ~MVCqtActor();

        /*
         * We don't want to pass the query register through the constructor because
         * the user would need to instantiate it. No sense. It is set by the controller before the start.
         * It's also cleaner.
         */
        void setQueryRegister(UiQueriesRegister* _query_register);

    public slots:
        void controller_channel_rx(const QString cmd);

    protected:
        UiQueriesRegister* query_register;
        bool running; // true when it receives the start cmd

        virtual void actorStart() = 0;
        virtual void actorStop() = 0;
        virtual bool cmds_controller_channel(const QString cmd) = 0; // must return true if the comand has been recognized else false

    private:
        void startActor();
        void endActor();

    signals:
        void controller_channel_tx(const QString cmd);

};

#endif // MVCQTACTOR_H
