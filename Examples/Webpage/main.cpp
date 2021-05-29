#include <backend/include/modelImp.h>

int main()
{
    MVCqt<MVCqtModelImp> framework(new MVCqtModelImp());
    framework.registerModelRpc("hello", &MVCqtModelImp::printHello);
    framework.start();
    return 0;
}
