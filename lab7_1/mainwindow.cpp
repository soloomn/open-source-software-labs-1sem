#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QMenuBar>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QAction* act = ui->menubar->addAction("Выбор цвета"); // добавляем в меню кнопку без выпадающего списка
    act->setShortcut(QString("Alt+C")); // устанавливаем акселератор
    connect(act, SIGNAL(triggered()), this, SLOT(showDialog())); // при нажатии на кнопку в меню должно появиться окно для выбора цвета

    p[0] = p[1] = QPoint(0,0); // задаем начальные значения:
    color = QColor(0,100,100);
    drawMode = false;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showDialog()
{
    color = QColorDialog::getColor(); // считываем цвет
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) // если нажата левая кнопка мыши
    {
        drawMode = true; // устанавливаем признак рисования
        p[0] = e->pos(); // запоминаем координаты начальной точки
    }

    if (e->button() == Qt::RightButton) // если нажата правая кнопка
    {
        color = QColor(0,100,100); // восстанавливаем первоначальный цвет
        DrawBuffer.clear(); // очищаем списки
        ColorBuffer.clear();
        drawMode = false; // правой кнопкой запретим рисовать
        update(); // перерисовываем окно
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    if (drawMode) // если установлен режим рисования
    {
        p[1] = e->pos(); // запоминаем текущую точку
        DrawBuffer.append(QLine(p[0],p[1])); // добавляем линию в список
        ColorBuffer.append(color); // добавляем текущий цвет в список
        p[0] = p[1]; // текущую точку делаем начальной для следующего фрагмента линии
        update();
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if (DrawBuffer.size() < 1) return; // если рисовать нечего, выходим из функции
    QPainter painter(this);

    QList<QLine>::const_iterator it = DrawBuffer.begin(); // объявляем итераторы для работы со списками:
    QList<QColor>::const_iterator cit = ColorBuffer.begin();

    // перерисовываем линии:
    do
    {
        painter.setPen(*cit++); // определяем перо того цвета, которое хранится в списке
        painter.drawLine(*it++); // рисуем фрагмент линии
    } while (it!= DrawBuffer.end()); // повторяем рисование, пока не закончится список
}
