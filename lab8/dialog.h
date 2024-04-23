#ifndef DIALOG_H
#define DIALOG_H
#include <QDialog>

namespace Ui {
    class Dialog;
}
class MainWindow; // С помощью этого класса объявим указатель на родительское окно
class Dialog : public QDialog
{
    Q_OBJECT
public: // Измените тип указателя на MainWindow
    explicit Dialog(MainWindow *parent = 0);

    ~Dialog();
    MainWindow* Parent; /* С помощью этого указателя диалоговое окно будет переда¬вать новое значение цвета главному окну */
 //  объявление слота, который будет передавать новое значение цвета главному окну:
public slots:
    void setR(int);
    void setG(int);
    void setB(int);
private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
