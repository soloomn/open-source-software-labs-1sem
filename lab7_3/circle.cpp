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

QPoint* Circle::drstar(QPoint p1)
{
    int n = 5;
    double cost = p1.x() / r;
    double sint= p1.y() / r;
    double tgt = sint / cost;

    QPoint* v = new QPoint[n]; // создаем массив для хранения вершин
    v[0] =  p + QPoint(-r,0); // начальная вершина многоугольника
    //v[0] =  p1; // начальная вершина многоугольника

    double da = 2 * M_PI / n; // угол между вершинами
    double a = 0; // угол, соотвествующий очередной вершине

    for (int i = 1; i < n; ++i)
    // проходим вершины (кроме начальной)
    {
        a += 2 * da; // изменяем угол
        // вычисляем координаты:
        v[i].setX(p.x() - r*cos(a));
        v[i].setY(p.y() + r*sin(a));

    }

    /*QPoint b,c,d,e,f;
    b = v[0]; c = v[1]; d = v[2]; e = v[3]; f = v[4];
    v[0] = b; v[1] = d; v[2] = f; v[3] = c; v[4] = e;*/

    return v;

}

Circle& Circle::operator =(const Circle & circle) // перегрузка оператора присваивания
{
    p = circle.p;
    r = circle.r;
    color = circle.color;
    return *this;
}
