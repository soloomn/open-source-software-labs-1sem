#include "dialog.h"
#include "ui_dialog.h"
#include <math.h>
#include <QTextCodec>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    adjustSize();
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    QString message;

    double a = ui->lineEdit->text().toDouble();
    double b = ui->lineEdit_2->text().toDouble();
    double c = ui->lineEdit_3->text().toDouble();
    double x1 = 0,x2 = 0;
    if ( a != 0 ) // Solving a quadratic equation:
    {
        double d = b*b - 4*a*c; // discriminant formula
        if ( d > 0 )
        {
          x1 = (-b + sqrt(d)) / (2*a);
          x2 = (-b - sqrt(d)) / (2*a);
          message = "The equation has two roots: " + QString::number(x1) + " and " + QString::number(x2);
          ui->textEdit->setText(message);
        }
        else if ( d == 0 )
        {
          x1=(-b) / (2*a);
          message = "The equation has one root: " + QString::number(x1);
          ui->textEdit->setText(message);
        }
        else
          ui->textEdit->setText("There are no valid roots");
    }
    else  // Solving a linear equation b*x + c = 0:
    {
        if (b)   // If  b != 0
        {
            x1 = -c / b;
            message = "The equation has one root: " + QString::number(x1);
            ui->textEdit->setText(message);
        }
        else if (!c) // If с == 0
        ui->textEdit->setText("The solution to the equation is any number");
        else
            ui->textEdit->setText("The equation has no solutions");
    }
}




void Dialog::on_pushButton_2_clicked()
{
    close();
}
