#ifndef MVCQTVIEW_H
#define MVCQTVIEW_H

#include <QObject>

class MVCqtView : public QObject
{
    Q_OBJECT

    public:
        explicit MVCqtView(QObject *parent = nullptr);
        ~MVCqtView();

    public slots:
        void controller_channel_rx(QString cmd);


};

#endif // MVCQTVIEW_H
