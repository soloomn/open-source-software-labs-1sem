#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

QString Dialog::GetSym()
{
    return ui->lineEdit->text();
}


Dialog::~Dialog()
{
    delete ui;
}
