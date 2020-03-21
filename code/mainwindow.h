#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleSpinBox>

#include <random>

#include "painter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Painter *painter;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

signals:
    void signal_draw();

public slots:
    void slot_process(double);
};

#endif // MAINWINDOW_H
