#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "dialog.h"  // Обеспечивает возможность использования класса Dialog
#define maxR 100 // максимальное количество строк
#define maxC 100 // максимальное количество столбцов

namespace Ui
{
    class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void paintEvent(QPaintEvent *); // автоматически вызывается при перерисовке окна
    void createMatrices(); // функция, размещающая в памяти матрицы полигонов и регионов
    void createNet(); // формирование сетки в рабочей области окна
    void createPolygon(int, int); // создание одной ячейки с заданными номерами
    void mousePressEvent(QMouseEvent *); // автоматически вызыватся при щелчке мышью
    void resizeEvent(QResizeEvent *); // автоматически вызывается при создании окни и при изменении его размеров

    void setfieldclear()
    {
        for (int i = 0; i < maxR; ++i)
              for (int j = 0; j<maxC; ++j)
                  Color[i][j] = QColor(0, 100, 100); // Заполняем матрицу начальным цветом
    }

    QPolygon** Polygon; // Указатель на матрицу полигонов
    QRegion** Region; // Указатель на матрицу областей

    Dialog* dlg; // объект, описывающий диалоговое окно
    int R; // значение яркости красного цвета
    int G; // значение яркости зелёного цвета
    int B; // значение яркости синего цвета

    QColor Color[maxR][maxC]; /* матрица для хранения цвета в каждой ячейке, она должна быть максимальных размеров, поскольку мы заранее не знаем размеры окна */

    int previousRows, rows, columns; /* количество строк для предыдущего состояния окна, текущее количество строк, количество столбцов */
    double w, h; // размеры рабочего поля

    double size, x0, y0, r; // размер одной ячейки, центр и радиус окружности, в которую вписан многоугольник

    QBrush brush; // кисть

private:
    Ui::MainWindow *ui;

private slots:
    void on_actionDialog_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionClear_triggered();
};
#endif // MAINWINDOW_H

