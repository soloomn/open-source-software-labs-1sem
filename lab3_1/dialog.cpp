#include "dialog.h"
#include "ui_dialog.h"
#include <cmath>
#include <QMessageBox>
#include <QtGui>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    adjustSize();
}

// вызов осуществлять так: a - сторона к которой проведена биссектриса, b и c - две другие стороны
double biss(double a, double b, double c)
{
    double bs = (sqrt(b*c*(a+b+c)*(b+c-a))/(b+c));
    return bs;
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    double a = ui->lineEdit->text().toDouble();
    double b = ui->lineEdit_2->text().toDouble();
    double c = ui->lineEdit_3->text().toDouble();
    QString text;
    if (a>0 && b>0 && c>0)
        {
            if (a+b>c && a+c>b && b+c>a)
            {
                text = "треугольник существует \n";
                text = text + "его биссектриссы: \n";
                text = text + "биссектрисса к a: " + QString::number(biss(a,b,c)) + "\n" + "биссектрисса к b: " + QString::number(biss(b,a,c)) + "\n" +
                        "биссектрисса к c: " + QString::number(biss(c,a,b)) + "\n";
            }
            else
            {
                text = "треугольник не существует";
            }
        }
    else
    {
        QMessageBox::critical(this, "сообщение об ошибке", "стороны должны быть больше 0!");
    }

    ui->listWidget->clear();
    ui->listWidget->addItem(text);
}
