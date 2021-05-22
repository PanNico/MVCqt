/*
* MIT License
* Copyright (c) 2021 Nicola Pancheri
* pancheri.nicola@gmail.com
*/

#include <QtTest>
#include <MVCqt/MVCqtModel/mvcqtModel.h>

class MVCqtModel_UnitTest : public QObject
{
    Q_OBJECT

    public:
        MVCqtModel_UnitTest();
        ~MVCqtModel_UnitTest();


    public slots:
        void controller_channel_rx(QString msg);

    private:
        MVCqtModel model;

    private slots:
        void test_case1();
        void test_case2();
        void test_case3();

    signals:
        void controller_channel_tx(QString msg);
};

MVCqtModel_UnitTest::MVCqtModel_UnitTest()
{
    connect(this, &MVCqtModel_UnitTest::controller_channel_tx, &model, &MVCqtModel::controller_channel_rx );
    connect(&model, &MVCqtModel::controller_channel_tx, this, &MVCqtModel_UnitTest::controller_channel_rx );
}

MVCqtModel_UnitTest::~MVCqtModel_UnitTest()
{
    emit controller_channel_tx("stop");
}

void MVCqtModel_UnitTest::test_case1()
{
    emit controller_channel_tx("start");
}

void MVCqtModel_UnitTest::test_case2()
{
    emit controller_channel_tx("hello");
}

void MVCqtModel_UnitTest::test_case3()
{
    emit controller_channel_tx("fail");
}

void MVCqtModel_UnitTest::controller_channel_rx(QString msg)
{
#ifdef MVC_QT_DEBUG
    msg="MVCqtModel_UnitTest controller_channel_rx recived: "+msg;
    print_str(msg);
#endif
}

QTEST_APPLESS_MAIN(MVCqtModel_UnitTest)

#include "tst_mvcqtmodel_unittest.moc"
