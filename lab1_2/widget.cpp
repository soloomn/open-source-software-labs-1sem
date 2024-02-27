#include "widget.h"
#include "ui_widget.h"
#include <math.h>
#include <QtGui>
#include <QTextCodec>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    adjustSize();
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    double a = ui->lineEdit->text().toDouble();
        double b = ui->lineEdit_2->text().toDouble();
        double c = ui->lineEdit_3->text().toDouble();
        double d = ui->lineEdit_4->text().toDouble();
        double e = ui->lineEdit_5->text().toDouble();
        double f = ui->lineEdit_6->text().toDouble();
        double n = a*e - b*d;
        double k = a*f - c*d;
        double g = c*e - b*f;
        if (n == 0)
            {
                if (k == 0 && n == 0)
                {
                    if ((a == 0 && b == 0 && c != 0) || (d == 0 && e == 0 && f != 0))
                    {
                        ui->lineEdit_7->setText("no roots");
                        ui->lineEdit_8->setText("no roots");
                    }
                    else
                    {
                        ui->lineEdit_7->setText("solution is any number");
                        ui->lineEdit_8->setText("solution is any number");
                    }
                }
                else
                {
                    ui->lineEdit_7->setText("no roots");
                    ui->lineEdit_8->setText("no roots");
                }
            }
            else
            {

                double y = k/n;
                double x = g/n;
                ui->lineEdit_7->setText(QString::number(x));
                ui->lineEdit_8->setText(QString::number(y));
            }
}
