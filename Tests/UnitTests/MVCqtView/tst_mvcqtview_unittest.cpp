#include <QtTest>

#include <MVCqt/MVCqtView/mvcqtView.h>

class MVCqtView_UnitTest : public QObject
{
    Q_OBJECT

public:
    MVCqtView_UnitTest();
    ~MVCqtView_UnitTest();


    public slots:
        void controller_channel_rx(QString msg);

    private:
        MVCqtView view;

    private slots:
        void test_case1();
        void test_case2();
        void test_case3();

    signals:
        void controller_channel_tx(QString msg);
};

MVCqtView_UnitTest::MVCqtView_UnitTest()
{
    connect(this, &MVCqtView_UnitTest::controller_channel_tx, &view, &MVCqtView::controller_channel_rx );
    connect(&view, &MVCqtView::controller_channel_tx, this, &MVCqtView_UnitTest::controller_channel_rx );
}

MVCqtView_UnitTest::~MVCqtView_UnitTest()
{
    emit controller_channel_tx("stop");
}

void MVCqtView_UnitTest::test_case1()
{
    emit controller_channel_tx("start");
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
#ifdef MVC_QT_DEBUG
    msg="MVCqtView_UnitTest controller_channel_rx recived: "+msg;
    print_str(msg);
#endif
}


QTEST_APPLESS_MAIN(MVCqtView_UnitTest)

#include "tst_mvcqtview_unittest.moc"
