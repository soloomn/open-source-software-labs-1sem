#include "dialog.h"
#include "ui_dialog.h"
#include <QRegExpValidator>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QString a,b;
    QRegExp reg(("[a-zA-Z, ]+"));
    // regular expression describing a set of valid characters
    QRegExpValidator* valid = new QRegExpValidator(reg, this);
    // declare a pointer to a validator object that uses a regular expression
    ui->lineEdit->setValidator(valid); // set the validator for the lineEdit element intended for input data entry
    ui->lineEdit_2->setValidator(valid);
}


// Note that the original string is automatically passed to the slot:
QString SetofSymbols(QString str)
{
    QString strRez = ""; // string for output
    QList<QChar> rez; // list of characters to create a set
    for (int i = 0; i<str.length(); ++i)
    {
    // search through all characters of the source string
        if (!rez.contains(str[i]))
        {
    // if the symbol is not contained in the set
            rez << str[i];
        }
    }// add it to the list
    qSort(rez); // sort the list

    foreach(QChar ch, rez) // add each character in the list to the string
        strRez += ch;

    return strRez;
}


Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    QString a,b,res;
    a = ui->lineEdit->text();
    b = ui->lineEdit_2->text();
    a= SetofSymbols(a);
    b= SetofSymbols(b);
    for (int i = 0; i <a.length(); i++)
    {
        for (int j = 0; j <b.length(); j++)
        {
            if (a[i] == b[j])
                res = res + a[i];
        }
    }
    ui->lineEdit_3->setText(res);
}
