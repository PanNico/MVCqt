#include <QCoreApplication>
#include "test1.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Test1 prova;
    prova.start();

    return 0;
}
