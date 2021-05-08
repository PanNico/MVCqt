#ifndef MVCQTACTOR_H
#define MVCQTACTOR_H

#include <QObject>
#include "mvcqtDebug.h"

class MVCqtActor : public QObject
{
    Q_OBJECT

    public:
        explicit MVCqtActor(QObject *parent = nullptr);
        ~MVCqtActor();

    public slots:
        virtual void controller_channel_rx(QString cmd) = 0;

    protected:
        bool running; // true when it receives the start cmd
        virtual void actorStart() = 0;
        virtual void actorStop() = 0;

    private:
        void startActor();
        void endActor();

    signals:
        void controller_channel_tx(QString cmd);

};

#endif // MVCQTACTOR_H
