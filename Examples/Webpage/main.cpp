#include <backend/include/modelImp.h>

int main()
{
    MVCqt<WebPageModel> framework(new WebPageModel());
    framework.registerModelRpc("printHello", &WebPageModel::printHello);
    framework.start();
    return 0;
}
