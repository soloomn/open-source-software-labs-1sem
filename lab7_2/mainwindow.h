#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "circle.h" // обеспечивает использование типа Circle
namespace Ui {
    class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QPoint p[2]; // точки, которые определяют текущую окружность
    int r; // радиус

    bool drawMode; // признак рисования
    QList <Circle> DrawBuffer;// список окружностей (ради этой строчки мы создали класс Circle)
    QColor color; // цвет текущей окружности

    void mousePressEvent(QMouseEvent *); // обрабатывает нажатие кнопки мыши
    void mouseMoveEvent(QMouseEvent *); // обрабатывает движение мыши
    void mouseReleaseEvent(QMouseEvent *); // обрабатывает отпускание кнопки мыши
    void paintEvent(QPaintEvent *); // описывает, что нужно нарисовать в окне

public slots:

    void Annul(); // для кнопки «Отменить»
    void Clear(); // для кнопки «Очистить»
    void showDialog(); // для кнопки «Выбрать цвет»
    void save(); // для кнопки «Сохранить»
    void open(); // для кнопки «Открыть»
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
