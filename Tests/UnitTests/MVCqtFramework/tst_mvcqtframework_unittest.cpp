/*
* MIT License
* Copyright (c) 2021 Nicola Pancheri
* pancheri.nicola@gmail.com
*/

#include <QtTest>
#include <backend/include/modelImp.h>

class MVCqtFramework_UnitTest : public QObject
{
    Q_OBJECT

public:
    MVCqtFramework_UnitTest();
    ~MVCqtFramework_UnitTest();
    MVCqt framework;

private slots:
    void test_case1();

};

MVCqtFramework_UnitTest::MVCqtFramework_UnitTest():
    framework(new MVCqtModelImp())
{

}

MVCqtFramework_UnitTest::~MVCqtFramework_UnitTest()
{

}

void MVCqtFramework_UnitTest::test_case1()
{
    framework.start();
}

QTEST_APPLESS_MAIN(MVCqtFramework_UnitTest)

#include "tst_mvcqtframework_unittest.moc"
