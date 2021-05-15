#include <QtTest>

#include "MVCqt/MVCqtController/mvcqtController.h"

class MVCqtController_UnitTest : public QObject
{
    Q_OBJECT

    public:
        MVCqtController_UnitTest();
        ~MVCqtController_UnitTest();

    private:
        MVCqtController controller;

    private slots:
        void test_case1();

};

MVCqtController_UnitTest::MVCqtController_UnitTest()
{

}

MVCqtController_UnitTest::~MVCqtController_UnitTest()
{

}

void MVCqtController_UnitTest::test_case1()
{
    controller.start();
}

QTEST_APPLESS_MAIN(MVCqtController_UnitTest)

#include "tst_mvcqtcontroller_unittest.moc"
