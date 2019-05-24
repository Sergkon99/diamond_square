#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    painter = new Painter(ui->canvas);

    connect(this, &MainWindow::signal_draw, painter, &Painter::slot_draw);
    connect(ui->pb_generate, &QPushButton::clicked, painter, &Painter::slot_draw);
    connect(ui->pb_save_as, &QPushButton::clicked, painter, &Painter::slot_save_as);
    connect(ui->sb_r, QOverload<double>::of(&QDoubleSpinBox::valueChanged), painter, &Painter::slot_set_r);
    connect(painter, &Painter::signal_process, this, &MainWindow::slot_process);

    emit signal_draw();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_process(double val)
{
    ui->statusBar->showMessage(QString::number(val));
}
