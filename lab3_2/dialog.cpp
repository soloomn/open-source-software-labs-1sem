#include "dialog.h"
#include "ui_dialog.h"
#include <QRegExpValidator>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QRegExp reg(("[a-zA-Z, ]+"));
    // регулярное выражение, описывающее набор допустимых символов
    QRegExpValidator* valid = new QRegExpValidator(reg, this);
    // объявляем указатель на объект валидатор, использующий регулярное выражение
    ui->lineEdit->setValidator(valid); /* устанавливаем валидатор для элемента lineEdit, предназначенного для ввода исходных данных */
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
    foreach(QChar ch, rez) // каждый символ списка добавляем в строку
        rezstr += ch;

    ui->lineEdit_3->setText(rezstr);
}
