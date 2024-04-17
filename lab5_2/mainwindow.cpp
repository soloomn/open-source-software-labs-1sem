#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include <QFileDialog>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,  // указатель на родительское окно
                                                    "Открыть файл", // заголовок окна
                                                    QString(""), // выбор начинается с текущего каталога
                                                    QString("Текстовые файлы (*.txt);;Все файлы (*.*)") ); // фильтры для списка файлов
    if (!fileName.isEmpty()) // если имя файла выбрано
    {
        file.setFileName(fileName); // связываем объект file с физическим файлом
        file.open(QIODevice::ReadOnly|QIODevice::Text); // открываем файл для чтения
        QString filetext = "Файл " + fileName + ": \n"; // выводим название файла 
        text = file.readAll(); // считываем весь текст
        ui->textEdit->setText(text); // выводим текст файла на экран
    }

}

void MainWindow::on_actionSymbol_triggered()
{
    int counter = 0;
    QString symb;
    Dialog dlg; // объект, соответствующий диалоговому окну

    dlg.move(420,220); // определяем положение окна на экране

    if(dlg.exec()==QDialog::Accepted) // выводим окно на экран и если была нажата кнопка <OK>
    {
        symb = dlg.GetSym();
        for (int i = 0; i <= text.length(); i++)
        {
            if (text[i] == symb)
            {
                counter++;
            }
        }
    }

    text = text + "\nЗаданный символ: " + symb + " встречается в тексте " + QString::number(counter) + " раз";
    ui->textEdit->setText(text); // выводим текст файла на экран
}

