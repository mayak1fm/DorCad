#include <QtCore>
#include <QTest>
#include <QApplication>
#include "ProjectBase.h"
#include "roadcadast.h"
#include "mainwindow.h"
#include "dorcad_tests.h"


int main(int argc, char *argv[])
{
    freopen("testing.log", "w", stdout);
    QApplication a(argc, argv);
    QTest::qExec(new DorCad_Tests, argc, argv);
    MainWindow w;
    w.setWindowTitle("DorCad");
    w.show();




     return a.exec();
}
