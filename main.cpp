#include "mainwindow.h"
#include <QApplication>
#include "loader.h"
#include <iostream>
#include "maillage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Maillage m;
    m.addPoint(0,0,0);
    m.addPoint(1,0,0);
    m.addPoint(0,1,0);
    m.addPoint(0.5,0.2,0);
    return a.exec();
}
