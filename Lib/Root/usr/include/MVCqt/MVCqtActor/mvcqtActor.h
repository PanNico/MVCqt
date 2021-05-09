#ifndef MVCQTACTOR_H
#define MVCQTACTOR_H

#include <QObject>
#include <QString>
#include "mvcqtDebug.h"

class MVCqtActor : public QObject
{
    Q_OBJECT

    public:
        explicit MVCqtActor(QObject *parent = nullptr);
        ~MVCqtActor();

    public slots:
        void controller_channel_rx(const QString cmd);

    protected:
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
