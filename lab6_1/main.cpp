#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(400,400); // задаем размер окна
    w.move(450,250); // перемещаем окно в центр экрана
    w.show();
    return a.exec();
}
