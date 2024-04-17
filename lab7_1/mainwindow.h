#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void mousePressEvent(QMouseEvent *e); // функция, вызываемая при нажатии кнопки мыши
    void mouseMoveEvent(QMouseEvent *e); // функция, вызываемая при движении мыши
    void paintEvent(QPaintEvent *); // функция, автоматически вызываемая при перерисовке окна

    QColor color; // цвет линий
    QPoint p[2]; // точки, определяющие линию (фрагмент траектории движения мыши)
    bool drawMode; // признак рисования
    QList<QLine> DrawBuffer; // список для хранения линий
    QList<QColor> ColorBuffer; // список для хранения цветов линий

public slots:
    void showDialog(); // слот, вызываемый при нажатии кнопки в меню



private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
