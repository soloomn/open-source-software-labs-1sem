#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pole.h"
#include <QScrollArea>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QScrollArea* scroll = new QScrollArea(this); // scroll area
    Pole* pole = new Pole(scroll);  // create a new widget
    scroll->setWidget(pole);  // place the widget in the scroll area
    setCentralWidget(scroll);  // make the scroll area the working area of the window
    connect(ui->actionOpen, SIGNAL(triggered()), pole, SLOT(fileOpen())); // bind the FileOpen command call to the slot we will create in the Pole class
}
MainWindow::~MainWindow()
{
    delete ui;
}


