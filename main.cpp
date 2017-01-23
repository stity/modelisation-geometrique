#include "mainwindow.h"
#include <QApplication>
#include "loader.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Loader loader = Loader();
    loader.load("queen.off");

    return a.exec();
}
