#ifndef POLE_H
#define POLE_H
#include <QWidget>
#include <QtGui>
#include <QScrollArea>

class Pole : public QWidget
{
    Q_OBJECT
public:
    explicit Pole(QScrollArea* parent = 0); // change the type of the pointer to the parent window
    QScrollArea* Parent; // scroll area pointer
    void paintEvent(QPaintEvent *); // redraws the window contents
    QFile file; // file containing an array
    QString fileName; // file name
    QVector<double> v; // array
    QVector<double> copyV; // copy of array
    QFont font; // font
    int dy; // distance between array elements when displaying on the screen
    int k; // number of array elements
    void Pie(QPainter&, QRect&, int, int, int); // draws one piece of the diagram
signals:
public slots:
    void fileOpen(); // slot that reads an array from a file
};
#endif // POLE_H
