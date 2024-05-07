#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int n, m; // количество вершин многоугольника и шаг прохождения через вершины
    int counter; // счетчик щелчков мышью
    bool flag; // признак окончания ввода
    double koef; // масштабный коэффициент для перевода радиуса в см

    QPoint p[2]; // точки, по которым мы щелкаем мышью
    QString str; // строка, которая хранит задаваемые числа
    QLabel *label1, *label2; // панели для строки состояния

    void paintEvent(QPaintEvent *); // эта функция автоматически вызывается при перерисовке окна
    void mousePressEvent(QMouseEvent *); // вызывается при нажатии кнопки мыши
    void keyPressEvent(QKeyEvent *); // вызывается при нажатии клавиши на клавиатуре


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
