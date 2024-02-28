#include "dialog.h"
#include "ui_dialog.h"
#include <QtDebug>  //  Enables qDebug()
#include <math.h>  //  Enables the operation of math functions
#include <QMessageBox> //  Provides for the use of a message window
#include <QtWidgets>


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
    adjustSize();
}


void Dialog::on_pushButton_clicked()
{
    double x = ui->lineEdit->text().toDouble();
    double eps = ui->lineEdit_2->text().toDouble();
    if (x > 0)
    {
        if (eps > 0 && eps < 1)
        {
            double y1, y2 = x;
            do
            {
                y1 = y2;
                y2 = y1 + 1./3*((x/(y1*y1))-y1);
                qDebug() << "intermediate value: " << y2;
            } while (abs(y2-y1)>=eps);
            ui->lineEdit_3->setText(QString::number(y2));
            double prov = pow(x,1./3);
            ui->lineEdit_4->setText(QString::number(prov));
        }
        else
        {
            ui->lineEdit_2->setText("");
            QMessageBox::critical(this, "error message", "accuracy must not exceed 1 or be less than 0!");
        }

    }
    else
    {
        ui->lineEdit->setText("");
        QMessageBox::critical(this, "error message", "x must be positive!");
    }
}
