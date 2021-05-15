#include "../include/mvcqtDebug.h"

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
