#include "dialog.h"
#include "ui_dialog.h"
#include <QRegExpValidator>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QRegExp reg(("[a-zA-Z, ]+"));
    // regular expression describing a set of valid characters
    QRegExpValidator* valid = new QRegExpValidator(reg, this);
    // declare a pointer to a validator object that uses a regular expression
    ui->lineEdit->setValidator(valid); // set the validator for the lineEdit element intended for input data entry
    ui->lineEdit_2->setValidator(valid);
}


Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    QString a,b,rezstr;
    a = ui->lineEdit->text();
    b = ui->lineEdit_2->text();
    QList<QChar> rez;
    for (int i = 0; i <a.length(); i++)
    {
        if ((!rez.contains(a[i])) && (b.contains(a[i])))
        {
            rez << a[i];
        }
    }
    qSort(rez);
    foreach(QChar ch, rez) // add each character in the list to the string
        rezstr += ch;

    ui->lineEdit_3->setText(rezstr);
}
