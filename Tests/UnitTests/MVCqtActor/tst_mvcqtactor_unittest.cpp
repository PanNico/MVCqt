#include <QtTest>
#include <MVCqt/MVCqtActor/mvcqtActor.h>

class MVCqtActor_UnitTest : public QObject
{
    Q_OBJECT

    public:
        MVCqtActor_UnitTest();
        ~MVCqtActor_UnitTest();

    public slots:
        void controller_channel_rx(QString msg);

    private:
        MVCqtActor actor;
    private slots:
        void test_case1();
        void test_case2();

    signals:
        void controller_channel_tx(QString msg);
};

MVCqtActor_UnitTest::MVCqtActor_UnitTest()
{
    connect(this, &MVCqtActor_UnitTest::controller_channel_tx, &actor, &MVCqtActor::controller_channel_rx );
    connect(&actor, &MVCqtActor::controller_channel_tx, this, &MVCqtActor_UnitTest::controller_channel_rx );
}

MVCqtActor_UnitTest::~MVCqtActor_UnitTest()
{
    emit controller_channel_tx("stop");
}

void MVCqtActor_UnitTest::test_case1()
{
    emit controller_channel_tx("start");
}

void MVCqtActor_UnitTest::test_case2()
{
    emit controller_channel_tx("fail");
}

void MVCqtActor_UnitTest::controller_channel_rx(QString msg)
{
#ifdef MVC_QT_DEBUG
    msg="MVCqtActor_UnitTest controller_channel_rx recived: "+msg;
    print_str(msg);
#endif
}

QTEST_APPLESS_MAIN(MVCqtActor_UnitTest)

#include "tst_mvcqtactor_unittest.moc"
