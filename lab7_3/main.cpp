#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.move(400, 250); // перемещает окно к центру экрана
    w.show();
    return a.exec();
}
