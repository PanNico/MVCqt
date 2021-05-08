#ifndef MVCQTDEBUG_H
#define MVCQTDEBUG_H

#define MVC_QT_DEBUG

#ifdef MVC_QT_DEBUG

#include <iostream>
#include <sstream>
#include <QString>

void print_str(std::string msg)
{
    std::cout << msg << std::endl;
}

void print_str(std::ostringstream &msg)
{
    std::cout << msg.str() << std::endl;
}


void print_str(QString &msg)
{
    std::cout << msg.toStdString() << std::endl;
}

#endif

#endif // MVCQTDEBUG_H
