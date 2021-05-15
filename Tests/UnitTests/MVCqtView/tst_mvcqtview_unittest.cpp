#include <QtTest>
#include <QApplication>
#include <MVCqt/MVCqtView/mvcqtView.h>
#include <QPointer>

static int argc=1;
static char* argv[]={"MVCqtView_UnitTest"};

class MVCqtView_UnitTest : public QObject
{
    Q_OBJECT

public:
    MVCqtView_UnitTest();
    ~MVCqtView_UnitTest();


    public slots:
        void controller_channel_rx(QString msg);

    private:
        QApplication appl;
        QPointer<MVCqtActor> view;

    private slots:
        void test_case1();
        void test_case2();
        void test_case3();

    signals:
        void controller_channel_tx(QString msg);
};

MVCqtView_UnitTest::MVCqtView_UnitTest() :
    appl(argc, argv),
    view(new MVCqtView("/home/nicola/Documenti/Progetti/MVCqt/HtmlTemplates/Dimension/", 1000, 900))
{

    connect(this, &MVCqtView_UnitTest::controller_channel_tx, view.data(), &MVCqtView::controller_channel_rx );
    connect(view.data(), &MVCqtView::controller_channel_tx, this, &MVCqtView_UnitTest::controller_channel_rx );
}

MVCqtView_UnitTest::~MVCqtView_UnitTest()
{
    emit controller_channel_tx("stop");
}

void MVCqtView_UnitTest::test_case1()
{
    emit controller_channel_tx("start");
    appl.exec();
}

void MVCqtView_UnitTest::test_case2()
{
    emit controller_channel_tx("hello");
}

void MVCqtView_UnitTest::test_case3()
{
    emit controller_channel_tx("fail");
}

void MVCqtView_UnitTest::controller_channel_rx(QString msg)
{
    if(msg=="exit")
        appl.exit();

#ifdef MVC_QT_DEBUG
    msg="MVCqtView_UnitTest controller_channel_rx recived: "+msg;
    print_str(msg);
#endif

}


QTEST_APPLESS_MAIN(MVCqtView_UnitTest)

#include "tst_mvcqtview_unittest.moc"
