#ifndef PAINTER_H
#define PAINTER_H

#include <QObject>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QTime>
#include <QFileDialog>

#include <random>

class Painter : public QObject
{
    Q_OBJECT

    std::random_device rd;

    QPixmap *pixmap;
    QPainter *painter;
    QLabel *canvas;
    QVector<QVector<double>> canvas_pixmap;
    int size;

    double r = 0.1;

    void clear_canvas();
    void init_canvas();
    void square(int, int, int, int);
    void diamond(int, int, int, int);
    void diamond(int, int ,int);
    void diamond_square(int, int, int, int);
    QColor color_by_height(int);

public:
    explicit Painter(QObject *parent = nullptr);
    Painter(QLabel *);

    void save_as();

    void draw();

signals:
    void signal_process(double);

public slots:
    void slot_draw();
    void slot_set_r(double);
    void slot_save_as();
};

#endif // PAINTER_H
