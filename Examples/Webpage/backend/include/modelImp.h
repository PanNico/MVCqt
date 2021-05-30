#ifndef MODELIMP_H
#define MODELIMP_H

#include <MVCqt/mvcqt.h>

class MVCqtModelImp : public MVCqtModel
{
    public:
        MVCqtModelImp();
        void run() override;

        void printHello(){
            std::cout << "\n################## Print hello! ##################" << std::endl;
        }
};

#endif // MODELIMP_H
