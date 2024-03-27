#include <QtGui>
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.move(400,200); // перемещаем окно по экрану
    w.show();
    return a.exec();
}
