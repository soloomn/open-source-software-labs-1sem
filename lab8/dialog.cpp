#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
 // обеспечивает возможность использования класса MainWindow
Dialog::Dialog(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->spinBox->setRange(0, 255); // Задаем диапазон изменнения значений наборного счетчика
    ui->spinBox->setSingleStep(5);// при щелчке по стрелочке значение счетчика будет изменяться на 5

    ui->spinBox_2->setRange(0, 255); // Задаем диапазон изменнения значений наборного счетчика
    ui->spinBox_2->setSingleStep(5);// при щелчке по стрелочке значение счетчика будет изменяться на 5

    ui->spinBox_3->setRange(0, 255); // Задаем диапазон изменнения значений наборного счетчика
    ui->spinBox_3->setSingleStep(5);// при щелчке по стрелочке значение счетчика будет изменяться на 5

    Parent = parent; // Указатель, объявленный в классе, становится равным значению локального указателя

    ui->spinBox->setValue(Parent->R); /* Устанавливаем начальное значение счетчика так, чтобы оно было равно начальному значению цвета, установленного в конструкторе главного окна */
    connect(ui->spinBox, SIGNAL(valueChanged(int)),
            this, SLOT(setR(int)));  /* связываем сигнал об изменении значения счетчика со слотом, который передает новое значение цвета главному окну */

    ui->spinBox_2->setValue(Parent->G); /* Устанавливаем начальное значение счетчика так, чтобы оно было равно начальному значению цвета, установленного в конструкторе главного окна */
    connect(ui->spinBox_2, SIGNAL(valueChanged(int)),
            this, SLOT(setG(int)));  /* связываем сигнал об изменении значения счетчика со слотом, который передает новое значение цвета главному окну */

    ui->spinBox_3->setValue(Parent->B); /* Устанавливаем начальное значение счетчика так, чтобы оно было равно начальному значению цвета, установленного в конструкторе главного окна */
    connect(ui->spinBox_3, SIGNAL(valueChanged(int)),
            this, SLOT(setB(int)));  /* связываем сигнал об изменении значения счетчика со слотом, который передает новое значение цвета главному окну */

}
Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setR(int R) /* значение n автоматически передается слоту от наборного счетчика с помощью сигнала valueChanged(int)*/
{
    Parent->R = R; // передаем значение цвета переменной, объявленной в классе гланого  окна
    Parent->update(); // посылаем сигнал «перерисовать окно»
}

void Dialog::setG(int G) /* значение n автоматически передается слоту от наборного счетчика с помощью сигнала valueChanged(int)*/
{
    Parent->G = G; // передаем значение цвета переменной, объявленной в классе гланого  окна
    Parent->update(); // посылаем сигнал «перерисовать окно»
}

void Dialog::setB(int B) /* значение n автоматически передается слоту от наборного счетчика с помощью сигнала valueChanged(int)*/
{
    Parent->B = B; // передаем значение цвета переменной, объявленной в классе гланого  окна
    Parent->update(); // посылаем сигнал «перерисовать окно»
}
