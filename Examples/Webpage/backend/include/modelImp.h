#ifndef MODELIMP_H
#define MODELIMP_H

#include <MVCqt/mvcqt.h>

class WebPageModel : public MVCqtModel
{
    public:
        WebPageModel();
        void run() override;

        void printHello(){
            print_str( "\n################## Print hello! ##################\n");
        }
};

#endif // MODELIMP_H
