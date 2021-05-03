#ifndef MVCQTMODEL_H
#define MVCQTMODEL_H

#include <QObject>

class MVCqtModel : public QObject
{
    public:
       explicit MVCqtModel(QObject *parent = nullptr);
       ~MVCqtModel();

    public slots:
        void endApplication();
        void startApplication();

    signals:
        void showWindow( int );


};

#endif // MVCQTMODEL_H
