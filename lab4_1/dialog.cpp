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
    // регулярное выражение, описывающее набор допустимых символов
    QRegExpValidator* valid = new QRegExpValidator(reg, this);
    // объявляем указатель на объект валидатор, использующий регулярное выражение
    ui->lineEdit->setValidator(valid); /* устанавливаем валидатор для элемента lineEdit, предназначенного для ввода исходных данных */
    ui->lineEdit_2->setValidator(valid);
}


// Обратите внимание на то, что исходная строка автоматически передается слоту:
QString SetofSymbols(QString str)
{
    QString strRez = ""; // строка для вывода
    QList<QChar> rez; // список символов для создания множества
    for (int i = 0; i<str.length(); ++i)
    {
    // перебираем все символы исходной строки
        if (!rez.contains(str[i]))
        {
    // если символ не содержится во множестве
            rez << str[i];
        }
    }// добавляем его в список
    qSort(rez); // сортируем список

    foreach(QChar ch, rez) // каждый символ списка добавляем в строку
        strRez += ch;
    //ui->lineEdit_3->setText(strRez); // выводим результат
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
