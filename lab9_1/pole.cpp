#include "pole.h"
#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

Pole::Pole(QScrollArea* parent) : // change the type of the pointer to the parent window
    QWidget(parent)
{
    Parent = parent; // store the pointer value
}
void Pole::paintEvent(QPaintEvent *) // display the array on the screen
{
    QPainter painter(this);
    painter.setFont(font); // set the font

    int y = 20; // level from which the array output to the screen starts
    double sum = 0; // sum of array elements

    k = v.size(); // array size

    for (int i = 0; i < k; ++i) // loop through the array
    {
        painter.drawText(10, y, QString::number(v[i])); // display the next element of the array

        y += dy; // move to another line
        sum += v[i]; // add an element to the sum
    }

    copyV = v; // copy the array so that the original array is displayed on the screen without changes
    qSort(copyV.begin(), copyV.end(), qGreater<double>()); // sort the array copy in descending order to build the diagram

    QRect rectBase = Parent->rect(); // rectangle corresponding to the visible part of the scroll area
    QRect rect = rectBase; // rectangle in which we will draw the diagram

    int h = rectBase.height()-25; // slightly reduce the height of the rectangle
    double startAngle = 0; // initial angle for the first fragment of the diagram
    double spanAngle = 0;

    rect.setSize(QSize(h,h)); // define a square with height h
    rect.moveRight(rectBase.width()-25); // move the square to the right border of the window


    for (int i = 0; i < qMin(13, k); ++i)
    {
        spanAngle = 360 * 16.* copyV[i] / sum ; // angle between radii

        Pie(painter, rect, startAngle, spanAngle, i); // draw a sector using the function defined below
        startAngle += spanAngle; // move on to the next sector
    }

    if (k > 13) // display the other elements of the array in the sum
    {
        spanAngle = 360*16 - startAngle; // determine the size of the corresponding angle

        Pie(painter, rect, startAngle, spanAngle, 13); // draw the rest of the diagram
    }
}
void Pole::fileOpen()
{
    if (file.isOpen()) file.close();

    v.clear(); // delete the previously read array
    copyV.clear(); // and a copy of it

    fileName = QFileDialog::getOpenFileName(this, "Open a file", QString("/Users/tim/documents/programming/open-source-software-labs-2sem/lab9_1"),
               QString("Text files (*.txt);;All files (*.*)")); // read the file name using a special window

    if (!fileName.isEmpty()) // if the file name is selected
    {
        file.setFileName(fileName); // link the file object to a physical file on disk
        file.open(QIODevice::ReadOnly); // open the file

        QTextStream in(&file); // create a thread for working with files

        double x; // single number from the file

        while (true) // like an infinite loop to read data from a file
        {
            in >> x; // read out one number
            if (x < 0) // if the number is invalid
            {
                QMessageBox::critical(this, "Data error",
                                      "All numbers must be greater than 0");
                return;
            }
            if (!in.atEnd()) // if the file is incomplete
                v << x; // write the number
            else break; //
        }
        font = QFont("Serif", 12); //
        QFontMetrics fm(font); //
        dy = fm.height(); //
        k = v.size(); //
        int height = qMax(1500, 20 + k*dy); //
        this->resize(1500, height); //
     }
}
void Pole::Pie(QPainter & painter,QRect& rect, int startAngle, int spanAngle, int i)
{ //
        int c = i+1; //
        int I, R,G,B; //
        B = c % 2; c /= 2; //
        G = c % 2; c /= 2; //
        R = c % 2; c /= 2; //
        I = c % 2; //
        painter.setBrush(QBrush(QColor(I*100+R*155,I*100+G*155,I*100+B*155))); //
        painter.drawPie(rect, startAngle, spanAngle); //
}
