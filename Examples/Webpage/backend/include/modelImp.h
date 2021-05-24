#ifndef MODELIMP_H
#define MODELIMP_H

#include <MVCqt/mvcqt.h>

class MVCqtModelImp : public MVCqtModel
{
    Q_OBJECT

    public:
        MVCqtModelImp();
        void run() override;
};

#endif // MODELIMP_H
