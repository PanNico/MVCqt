/*
* MIT License
* Copyright (c) 2021 Nicola Pancheri
* pancheri.nicola@gmail.com
*/

#ifndef MVCQTDEBUG_H
#define MVCQTDEBUG_H

#define MVC_QT_DEBUG

#ifdef MVC_QT_DEBUG

#include <iostream>
#include <sstream>
#include <QString>

void print_str(std::string msg);
void print_str(std::ostringstream &msg);
void print_str(QString &msg);

#endif

#endif // MVCQTDEBUG_H
