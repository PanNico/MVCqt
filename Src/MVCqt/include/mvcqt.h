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
        explicit MVCqt(MVCqtModel* _backend, QObject *parent = nullptr);
        ~MVCqt();

        void start();

    private:
        class MVCqtConf{
            public:
                MVCqtConf(QString& _appName, int _windowHeight, int _windowWidth, bool _fullscreen) :
                    appName(_appName),
                    windowHeight(_windowHeight),
                    windowWidth(_windowWidth),
                    fullscreen(_fullscreen)
                {}

                QString appName;
                int windowHeight;
                int windowWidth;
                bool fullscreen;
        };

        MVCqtConf* config;
        MVCqtController* controller;
        QPointer<QApplication> appl;

        friend void readConfFile(MVCqt* _this);
        friend void validateConfFile(QJsonDocument& json_conf, MVCqt* _this);

};

#endif // MVCQT_H
