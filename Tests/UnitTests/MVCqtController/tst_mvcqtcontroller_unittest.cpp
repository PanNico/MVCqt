#include <QtTest>
#include <QApplication>
#include "MVCqt/MVCqtController/mvcqtController.h"

static int argc=1;
static char* argv[]={"MVCqtView_UnitTest"};

class MVCqtController_UnitTest : public QObject
{
    Q_OBJECT

    public:
        MVCqtController_UnitTest();
        ~MVCqtController_UnitTest();

    private:
        QApplication appl;
        MVCqtController controller;

    private slots:
        void test_case1();

};

MVCqtController_UnitTest::MVCqtController_UnitTest() :
    appl(argc, argv),
    controller("/home/nicola/Documenti/Progetti/MVCqt/HtmlTemplates/Dimension/", 1000, 900)
{

}

MVCqtController_UnitTest::~MVCqtController_UnitTest()
{

}

void MVCqtController_UnitTest::test_case1()
{
    controller.start();
    appl.exec();
}

QTEST_APPLESS_MAIN(MVCqtController_UnitTest)

#include "tst_mvcqtcontroller_unittest.moc"
