#ifndef MVCQTCONTROLLER_H
#define MVCQTCONTROLLER_H

#include <QObject>
#include <QThread>
#include <QSharedPointer>
#include <MVCqt/MVCqtActor/mvcqtActor.h>

class MVCqtController : public QObject
{
    Q_OBJECT

    public:
        explicit MVCqtController(QObject *parent = nullptr);
        ~MVCqtController();

        void start();

    public slots:
        void model_channel_rx(const QString cmd);
        void view_channel_rx(const QString cmd);

/*
    protected:
        virtual void connections() = 0;
        virtual void endActions() = 0;
*/
    private:
        QSharedPointer<MVCqtActor> model;
        QSharedPointer<MVCqtActor> view;
        QThread modelThread;
        QThread viewThread;

        void defaultConnections();

    signals:
        void model_channel_tx(const QString cmd);
        void view_channel_tx(const QString cmd);



};

#endif // MVCQTCONTROLLER_H
