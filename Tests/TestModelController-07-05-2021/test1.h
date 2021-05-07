#ifndef TEST1_H
#define TEST1_H

#include <MVCqt/mvcqt.h>

class Test1 : public MVCqtController
{
    Q_OBJECT

    public:
        Test1();
        ~Test1(){}

    private:
        void connections() override{

        }

        void endActions() override{

        }
};

#endif // TEST1_H
