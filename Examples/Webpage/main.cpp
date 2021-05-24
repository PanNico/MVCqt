#include <backend/include/modelImp.h>

int main()
{
    MVCqt framework(new MVCqtModelImp());
    framework.start();
    return 0;
}
