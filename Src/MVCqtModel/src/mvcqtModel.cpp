#include "../include/mvcqtModel.h"
#include <QDebug>

MVCqtModel::MVCqtModel(QObject *parent) :
    QObject(parent)
{
    qDebug() << "MVCqtModel created";
}

MVCqtModel::~MVCqtModel()
{
    qDebug() << "MVCqtModel destroied";
}

void MVCqtModel::startApplication()
{
    qDebug() << "MVCqtModel started";
}

void MVCqtModel::endApplication()
{
    qDebug() << "MVCqtModel ended";
}
