#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_verticalSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    void keyPressEvent(QKeyEvent * event);
    void mousePressEvent(QMouseEvent*e);
    void wheelEvent(QWheelEvent *event);

};

#endif // MAINWINDOW_H
