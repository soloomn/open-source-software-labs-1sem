#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>  // обеспечивает работу графического интерфейса
#include <QApplication>
#include <QLabel>
#include <QColor>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m = n = 1;
    counter = 0;
    flag = false;

    label1 = new QLabel(ui->statusbar); // создаем панель для строки состояния
    label1->setFrameStyle(QFrame::Panel | QFrame::Sunken); // задаем вид панели (утопленная)

    // то же самое для второй панели:
    label2 = new QLabel(ui->statusbar);
    label2->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    // Определяем вид строки состояния:
    QPalette pal = ui->statusbar->palette(); // считывам палитру строки состояния
    pal.setColor(QPalette::Background, QColor(215,220,210)); // задаем цвет фона строки состояния
    pal.setColor(QPalette::Foreground, QColor(0,50,0)); // Задаем цвет текста в стороке состояния

    ui->statusbar->setPalette(pal); // Устанавливаем новую палитру
    ui->statusbar->setAutoFillBackground(true); // Нужно вызвать эту функцию, чтобы строка состояния закрасилась
    ui->statusbar->setSizeGripEnabled(false); // запрещаем показ маркера изменения размеров окна (это не обязательно)

    // Добавляем в правую часть строки состояния панели:
    ui->statusbar->addPermanentWidget(label1);
    ui->statusbar->addPermanentWidget(label2);

    /* Определим разрешение экрана для определения масштабного коэффициента для пересчета размеров в см: */
    QDesktopWidget *desktop = QApplication::desktop();
    int width = desktop->width(); // ширина экрана в точках
    int height = desktop->height(); // высота экрана в точках

    qDebug() << width <<" "<< height; // можно посмотреть, что получилось
    koef = 2.54*19/sqrt(width*width+height*height); /* вычисляем длину диагонали в см (в данном случае предполагается, что длина диагонали 19 дюймов) и делим на длину диагонали в точках */
    qDebug()<<"koef = " << koef; // посмотрите значение масштабного коэффициента

}

MainWindow::~MainWindow()
{
    delete ui;
}

// функция, обрабатывающая щелчки мышью:
void MainWindow::mousePressEvent(QMouseEvent* event)
{
   if (event->button() == Qt::LeftButton) // если щелкнули левой кнопкой мыши
   {
           counter %= 2; // номер точки может быть равен 0 или 1
           p[counter++] = event->pos(); // записываем координаты точки, в которой пользователь щелкнул мышью
           update(); // перерисовываем окно
    }
}

// функция, обрабатывающая нажатие клавиш на клавиатуре:
void MainWindow::keyPressEvent(QKeyEvent *event )
{
   QRegExp reg("[0-9]{1,3} [0-9]{1}"); // позволим вводить первое число не более, чем из 3 цифр и второе - из одной
   QRegExpValidator* validator = new QRegExpValidator(reg, this); // создаем валидатор для проверки строки на основе регулярного выражения
   int pos = 0; // эта переменная нужна для вызова валидатора
   if (flag) // если клавиша <Enter> уже была нажата
   {
       str.clear(); // начинаем ввод сначала
       flag = false;
   }
   else
   {
      switch (event->key()) // проверяем, какая клавиша была нажата
      {
       case Qt::Key_Return: // если <Enter>:
          {
             QTextStream in(&str,QIODevice::ReadOnly); // создаем поток из строки
             in >> n >> m; // считываем n и m
             flag = true; // запоминаем, что ввод выполнен
          } break;

      case Qt::Key_Backspace: // обеспечиваем возможность стирания:
          {
             int len = str.length(); // определяем длину строки
             str.remove(len-1, 1); // удаляем последний символ
          } break;

      default: QString ch = event->text(); // если обычный символ, считываем его
                QString tmp = str + ch; // попробуем добавить его к строке
                if (validator->validate(tmp, pos)) // если временная строка соответствует шаблону
                    str += ch; // добавляем символ к используемой строке
       }
   }

   update(); // обновляем экран
   ui->statusbar->showMessage("Готово"); // Выводим сообщение в левой части строки состояния
}

// описываем, что нужно нарисовать в окне:
void MainWindow::paintEvent(QPaintEvent *)
{
   QPainter painter(this); // объект для рисования
   painter.setBrush(QBrush(QColor(0,255,255))); // кисть
   QRect rect(0,0,width(), height()); // прямоугольник окна
   painter.setFont(QFont("Bitstream Charter",12)); // шрифт
   int r = 0; // радиус окружности
   if (counter == 2) // если окружность задана, рисуем ее
   {
      painter.setPen(QPen(QColor(0,255,0), 1)); // перо
      r = sqrt(pow(p[0].x() - p[1].x(), 2) + pow(p[0].y() - p[1].y(), 2)); // радиус окружности
      painter.drawEllipse(p[0], r, r); // рисуем окружность с центром в точке p[0]

      if (flag) // если числа заданы
      {
         QPoint* v = new QPoint[n]; // создаем массив для хранения вершин
         v[0] = p[0] + QPoint(r,0); // начальная вершина многоугольника

         double da = 2 * M_PI / n; // угол между вершинами
         double a = 0; // угол, соотвествующий очередной вершине

         for (int i = 1; i < n; ++i) // проходим вершины (кроме начальной)
         {
             a += m * da; // изменяем угол
             // вычисляем координаты:
             v[i].setX(p[0].x() + r*cos(a));
             v[i].setY(p[0].y() - r*sin(a));
         }

         painter.setBrush(Qt::darkCyan); // цвет многоугольника
         painter.drawPolygon(v, n, Qt::WindingFill); // рисуем закрашенный многоугольник

      }
   }

// описываем вывод в зависимости от количества щелчков мышью:
painter.setPen(QPen(QColor(100, 0, 100), 3));// цвет текста

switch (counter)
{
   case 0:
    painter.drawText(10, 40, "Задайте окружность двумя щелчками мыши"); break;
   case 1:
    painter.drawEllipse(p[0].x(), p[0].y(), 2, 2); break;
   case 2:
    if (flag)
           painter.drawText(10, 40, "Задайте число разбиений и шаг " + str);
    else
           painter.drawText(10, 40, "Задайте число разбиений и шаг " + str + '_');
}

//   Выводим информацию с помощью панелей строки состояния:
QString text = QString("Координаты центра: %1, %2").arg(p[0].x()).arg(p[0].y());
label1->setText(text);

double rsm = r*koef; // радиус в см

text = QString(" радиус %1 см ").arg(rsm, 0,'f',1);
// выводим радиус с точностью 1 знак после точки
label2->setText(text);
}

