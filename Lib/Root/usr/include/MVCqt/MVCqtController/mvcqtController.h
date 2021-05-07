#ifndef MVCQTCONTROLLER_H
#define MVCQTCONTROLLER_H

#include <QObject>
#include <QThread>
#include <QSharedPointer>
#include <MVCqt/MVCqtModel/mvcqtModel.h>

class MVCqtController : public QObject
{
    Q_OBJECT

    public:
        explicit MVCqtController(QObject *parent = nullptr);
        ~MVCqtController();

        void start();

    public slots:
        void model_channel_rx(QString cmd);


    protected:
        virtual void connections() = 0;
        virtual void endActions() = 0;

    private:
        QSharedPointer<MVCqtModel> model;
     //   QThread modelThread;

        void defaultConnections();

    signals:
        void model_channel_tx(QString cmd);



};

#endif // MVCQTCONTROLLER_H
