#ifndef CIRCLE_H
#define CIRCLE_H
#include <QtGui>  // обеспечивает графическую систему
class Circle
{

public:
    QPoint p; // координаты центра окружности
    int r; // радиус
    QColor color; // цвет

    Circle(); // конструктор по умолчанию
    Circle(QPoint& _p, int _r, QColor col); // основной конструктор
    Circle(const Circle& ); // конструктор копирования

    Circle& operator = (const Circle& ); // оператор присваивания

};
#endif // CIRCLE_H

