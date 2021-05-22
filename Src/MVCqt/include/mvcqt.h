/*
* MIT License
* Copyright (c) 2021 Nicola Pancheri
* pancheri.nicola@gmail.com
*/

#ifndef MVCQT_H
#define MVCQT_H

#include <MVCqt/MVCqtController/mvcqtController.h>
#include <MVCqt/MVCqtModel/mvcqtModel.h>
#include <QApplication>
#include <QPointer>

class MVCqt : public QObject
{
    Q_OBJECT

    public:
        explicit MVCqt(MVCqtModel* backend, QObject *parent = nullptr);
        ~MVCqt();

        void start();

    private:
        MVCqtController* controller;
        QPointer<QApplication> appl;
};

#endif // MVCQT_H
