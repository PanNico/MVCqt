#ifndef MVCQTQCONTROLLER_H
#define MVCQTQCONTROLLER_H

#include <MVCqt/MVCqtActor/mvcqtActor.h>
#include <QApplication>
#include <QThread>
#include "rpcsChannel.h"
#include <memory>

/*
 * Allows to connect the model and view with signals and slots
 */
class MVCqtQController : public QObject {
    Q_OBJECT

    public:
        explicit MVCqtQController(std::shared_ptr<MVCqtActor> _model, MVCqtActor* _view, std::shared_ptr<QApplication> _qapp, RpcsChannel& _rpcs_channel);
        ~MVCqtQController();

    public slots:
        void start();

    private slots:
        void model_channel_rx(const QString cmd);
        void view_channel_rx(const QString cmd);
        void view_rx_rpc(const QString cmd);

    private:
        UiQueriesRegister query_register;
        std::shared_ptr<MVCqtActor> model;
        std::unique_ptr<MVCqtActor> view;
        std::shared_ptr<QApplication> qapp;
        RpcsChannel& rpcs_channel;
        QThread modelThread;
        void defaultConnections();

    signals:
        void model_channel_tx(const QString cmd);
        void view_channel_tx(const QString cmd);

};

#endif // MVCQTQCONTROLLER_H
