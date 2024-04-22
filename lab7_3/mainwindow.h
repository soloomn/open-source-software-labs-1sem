#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "dialog.h"  // Обеспечивает возможность использования класса Dialog
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

    Dialog* dlg; // объект, описывающий диалоговое окно
    int R; // значение яркости красного цвета
    int G; // значение яркости зелёного цвета
    int B; // значение яркости синего цвета


    bool drawMode; // признак рисования
    QList <Circle> DrawBuffer;// список окружностей (ради этой строчки мы создали класс Circle)
    QColor color; // цвет текущей окружности

    void mousePressEvent(QMouseEvent *); // обрабатывает нажатие кнопки мыши
    void mouseMoveEvent(QMouseEvent *); // обрабатывает движение мыши
    void mouseReleaseEvent(QMouseEvent *); // обрабатывает отпускание кнопки мыши
    void paintEvent(QPaintEvent *); // описывает, что нужно нарисовать в окне

public slots:
    void on_actionDialog_triggered();
    void Annul(); // для кнопки «Отменить»
    void Clear(); // для кнопки «Очистить»
    void save(); // для кнопки «Сохранить»
    void open(); // для кнопки «Открыть»
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
