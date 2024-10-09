#include "pole.h"
#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <string>
using namespace std;

Pole::Pole(QScrollArea* parent) :   // измените тип указателя на родительское окно
    QWidget(parent)
{
    Parent = parent; // запоминаем значение указателя
}

void Pole::paintEvent(QPaintEvent *) // отображаем массив на экране:
{
    QPainter painter(this);
    int y = 20 + dy; // уровень, с которого начинается вывод массива на экран
    int y1 = 20 + dy;
    int sch = 0;
    painter.setFont(font); // устанавливаем шрифт

    // Вывод массива:
    double sum = 0; // сумма элементтов массива
    k = v.size(); // размер массива



    for (int i = 0; i < k; ++i) // проходим по массиву
    {
        painter.drawText(10, y, QString::number(v[i])); // выводим очередной элемент массива на экран

        if (floor(v[i])  == v[i])
        {
            if (int(v[i]) % 2 == 0)
            {
                painter.drawText(100, y1, QString::number(v[i]));
                y1 += dy; // переходим на другую строку
                sch++;
            }
        }

        y += dy; // переходим на другую строку
        sum += v[i]; // добавляем элемент к сумме
    }

    copyV = v; // копируем массив, чтобы исходный массив отображался на экране без изменений
    qSort(copyV.begin(), copyV.end(), qGreater<double>()); // сортируем копию массива по убыванию, чтобы построить диаграмму

    painter.drawText(10, 20, "Массив:");
    QString t = "целые чётные числа: их количество = " + QString::number(sch);
    painter.drawText(100, 20, t);

    t = "Отсортированный массив:";
    y = y + 2 * dy;
    painter.drawText(10, y, t);
    for (int i = 0; i < k; ++i) // проходим по массиву
    {
        y += dy; // переходим на другую строку
        painter.drawText(10, y, QString::number(copyV[i])); // выводим очередной элемент массива на экран
    }

    // Диаграмма:
    QRect rectBase = Parent->rect(); // прямоугольник, соответствующий видимой части области прокрутки
    QRect rect = rectBase; // прямоугольник, в котором мы будем рисовать диаграмму

    int h = rectBase.height()-25; // несколько уменьшим высоту прямоугольника

    rect.setSize(QSize(h,h)); // задаем квадрат высотой h
    rect.moveRight(rectBase.width()-25); // перемещаем квадрат к правой границе окна

    double startAngle = 0; // начальный угол для первого фрагмента диаграммы
    double spanAngle = 0; // угол,

    for (int i = 0; i < qMin(13, k); ++i) //
    {
        spanAngle = 360 * 16.* copyV[i] / sum ; // Угол между радиусами
        Pie(painter, rect, startAngle, spanAngle, i); // рисуем сектор с помощью функции, определенной ниже
        startAngle += spanAngle; // переходим к следующему сектору
    }

    if (k > 13) // отображаем остальные элементы массива в сумме:
    {
        spanAngle = 360*16 - startAngle; // определяем размер соответствующего угла
        Pie(painter, rect, startAngle, spanAngle, 13); // рисуем оставшуюся часть диаграммы
    }
}


void Pole::fileOpen()
{
    if (file.isOpen()) file.close();
    v.clear(); // удаляем ранее считанный массив
    copyV.clear(); // и его копию
    fileName = QFileDialog::getOpenFileName(this, "Открыть файл", QString("/Users/tim/documents/programming/open-source-software-labs-2sem/lab9_2"),
               QString("текстовые файлы (*.txt);;Все файлы (*.*)"));// считываем имя файла с помощью специального окна

    if (!fileName.isEmpty()) // если имя файла выбрано
    {
        file.setFileName(fileName); // связываем объект файл с физическим файлом на диске
        file.open(QIODevice::ReadOnly); // открываем файл
        QTextStream in(&file); // создаем поток для работы с файлами
        double x; // одно число из файла
        while (true) // как бы бесконечный цикл для чтения данных из файла
        {
            in >> x; // считываем одно число
            if (x < 0) // если число недопустимо
            {
                QMessageBox::critical(this, "Ошибка в данных", "Все числа должны быть больше 0");
                return;
            }
            if (!in.atEnd()) // если файл не закончен
                v << x; // записываем число
            else break;
        }

        font = QFont("Serif", 12);
        QFontMetrics fm(font);
        dy = fm.height();
        k = v.size();

        int height = qMax(1500, 20 + k*dy);
        this->resize(1500, height);
        file.close();
     }
}

void Pole::fileSave()
{
    QString str;

    file.open(QIODevice::WriteOnly); // открываем сохраняемый файл
    QTextStream out(&file); // создаем поток, связанный с файлом (запись файла обычно выполняется с помощью потока)

    for (int i = 0; i < k; ++i)
    {
        str = str + QString::number(copyV[i]) + " ";
    }

    out << str;
    qDebug() << "данные записаны";

    file.close();
}

void Pole::Pie(QPainter & painter,QRect& rect, int startAngle, int spanAngle, int i)
{
        int c = i+1;
        int I, R,G,B;
        B = c % 2; c /= 2;
        G = c % 2; c /= 2;
        R = c % 2; c /= 2;
        I = c % 2;
        painter.setBrush(QBrush(QColor(I*100+R*155,I*100+G*155,I*100+B*155)));
        painter.drawPie(rect, startAngle, spanAngle);
}
