/*
* MIT License
* Copyright (c) 2021 Nicola Pancheri
* pancheri.nicola@gmail.com
*/

#include "../include/mvcqt.h"
#include <QtWebEngine>

static int argc=1;
static char* application_name[1];


MVCqt::MVCqt(MVCqtModel* _backend, QObject *parent) :
    QObject(parent)
{
    application_name[0]="nome";
    appl=new QApplication(argc, application_name);
    QtWebEngine::initialize();
    //TODO: reads config file to to get MVCqtController parameters
    controller = new MVCqtController(_backend,"/home/nicola/Documenti/Progetti/MVCqt/HtmlTemplates/Dimension/", 1000, 900);

}

MVCqt::~MVCqt()
{
    delete controller;
}

void MVCqt::start()
{
    controller->start();
    appl->exec();
}
