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
        QList<std::pair<QString, void (*)()>> command_list;

        void register_cmd(const QString cmd, void (*)());
        virtual void actorStart() = 0;
        virtual void actorStop() = 0;

    private:
      //  void startActor();
        void endActor();

    signals:
        void controller_channel_tx(const QString cmd);

};

#endif // MVCQTACTOR_H
