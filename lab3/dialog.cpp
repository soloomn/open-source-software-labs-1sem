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

// call as follows: a is the side to which the bisector is bisected, b and c are the other two sides
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
                text = "triangle exists \n";
                text = text + "its bisectors: \n";
                text = text + "bisector to a: " + QString::number(biss(a,b,c)) + "\n" + "bisector to b: " + QString::number(biss(b,a,c)) + "\n" +
                        "bisector to c: " + QString::number(biss(c,a,b)) + "\n";
            }
            else
            {
                text = "triangle doesn't exist";
            }
        }
    else
    {
        QMessageBox::critical(this, "error message", "sides must be greater than 0!");
    }

    ui->listWidget->clear();
    ui->listWidget->addItem(text);
}
