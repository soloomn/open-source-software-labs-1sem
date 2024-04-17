#include "circle.h"

Circle::Circle() // конструктор по умолчанию
{
    p = QPoint(0,0);
    r = 0;
    color = Qt::darkCyan;
}

Circle::Circle(QPoint &_p, int _r, QColor col = Qt::darkCyan) // основной конструктор
{
    p = _p;
    r = _r;
    color = col;
}

Circle::Circle(const Circle & circle) // конструктор копирования
{
    p = circle.p;
    r = circle.r;
    color = circle.color;
}

Circle& Circle::operator =(const Circle & circle) // перегрузка оператора присваивания
{
    p = circle.p;
    r = circle.r;
    color = circle.color;
    return *this;
}

