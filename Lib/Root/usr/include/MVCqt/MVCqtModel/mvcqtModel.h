#ifndef MVCQTMODEL_H
#define MVCQTMODEL_H

#include <QObject>

class MVCqtModel : public QObject
{
    Q_OBJECT

    public:
       explicit MVCqtModel(QObject *parent = nullptr);
       ~MVCqtModel();

    public slots:
        void controller_channel_rx(QString cmd);

    private:
        bool running; // true when it receives the start cmd

        void startModel();
        void endModel();

    signals:
        void controller_channel_tx(QString cmd);

};

#endif // MVCQTMODEL_H
