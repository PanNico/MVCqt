#include "../include/mvcqtDebug.h"
#include <QThread>

void print_str(std::string msg)
{
    std::cout << "Thread " << QThread::currentThreadId() << ": " << msg << std::endl;
}

void print_str(std::ostringstream &msg)
{
    std::cout << "Thread " << QThread::currentThreadId() << ": " << msg.str() << std::endl;
}


void print_str(QString &msg)
{
    std::cout << "Thread " << QThread::currentThreadId() << ": " << msg.toStdString() << std::endl;
}
