#include "mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    //w.showMaximized();

    return a.exec();
}
