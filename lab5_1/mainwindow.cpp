#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
    QFile file(":/test.txt"); /* объявляем файл, файл мы будем брать из ресурсов программы (на это указывает префикс « :/ » в имени файла  */
    if (file.exists()) // если файл найден
    {
        file.open(QIODevice::ReadOnly|QIODevice::Text); // открываем его
        QString text = file.readAll(); // считываем весь текст
        ui->textEdit->setText(text); // выводим текст файла на экран
    }
    else
        ui->textEdit->setText("Файл не найден");

}
