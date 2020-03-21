#include "painter.h"

void Painter::clear_canvas()
{
    painter->eraseRect(0, 0, canvas->width(), canvas->height());
}

void Painter::init_canvas()
{
    srand(QTime::currentTime().msec());

    canvas_pixmap[0][size - 1] = rand() % 161 - 80;
    canvas_pixmap[size - 1][size - 1] = rand() % 161 - 80;
    canvas_pixmap[0][0] = rand() % 161 - 80;
    canvas_pixmap[size - 1][0] = rand() % 161 - 80;
}

void Painter::square(int x1, int y1, int x2, int y2)
{
    int l = (x2 - x1) / 2;

    double arithmetic_mean = (canvas_pixmap[x1][y1] + canvas_pixmap[x2][y1] +
                              canvas_pixmap[x1][y2] + canvas_pixmap[x2][y2]) / 4.0;

    canvas_pixmap[x1 + l][y1 + l] = arithmetic_mean + r * (rand() % 3 - 1) * l;
}

void Painter::diamond(int x1, int y1, int x2, int y2)
{
    int l = (x2 - x1) / 2;
    diamond(x1, y1 + l, l);
    diamond(x2, y2 - l, l);
    diamond(x2 - l, y2, l);
    diamond(x1 + l, y1, l);
}

void Painter::diamond(int x, int y , int l)
{
    double a = 0, b = 0, c = 0, d = 0;
    if(y + l < size)
        a = canvas_pixmap[x][y + l];
    else
        a = canvas_pixmap[x][l];

    if(y - l >= 0)
        c = canvas_pixmap[x][y - l];
    else
        c = canvas_pixmap[x][size - l];

    if(x - l >= 0)
        b = canvas_pixmap[x - l][y];
    else
        b = canvas_pixmap[size - l][y];

    if(x + l < size)
        d = canvas_pixmap[x + l][y];
    else
        d = canvas_pixmap[l][y];

    canvas_pixmap[x][y] = (a + b + c + d) / 4 + r * (rand() % 3 - 1) * l;
}

// (x1,y1)........
//    .          .
//    .          .
//    ........(x2,y2)
void Painter::diamond_square(int x1, int y1, int x2, int y2)
{
    int l = (x2 - x1) / 2;
    if(l > 0){
        square(x1, y1, x2, y2);

        diamond(x1, y1 + l, l);
        diamond(x2, y2 - l, l);
        diamond(x2 - l, y2, l);
        diamond(x1 + l, y1, l);
    }
}

QColor Painter::color_by_height(int h)
{
/*
    8000    254, 159, 75
    6000    250, 216, 106
    4000    254, 243, 158
    2000    252, 245, 139
    1000    243, 255, 203
    500     233, 252, 170
    200     209, 147, 160
    0       167, 201, 114
    200     204, 248, 153
    500     206, 255, 249
    1000    176, 255, 249
    2000    152, 251, 255
    3000    126, 242, 255
    4000    129, 219, 253
    5000    100, 194, 255
    6000    88, 165, 253
    8000    70, 138, 249
*/
    if(h >= 80) return QColor(254, 159, 75);
    if(h >= 60) return QColor(250, 216, 106);
    if(h >= 40) return QColor(254, 243, 158);
    if(h >= 20) return QColor(252, 245, 139);
    if(h >= 10) return QColor(243, 255, 203);
    if(h >= 5) return QColor(233, 252, 170);
    if(h >= 2) return QColor(249, 248, 153);
    if(h >= 0) return QColor(167, 201, 114);
    if(h >= -2) return QColor(204, 248, 153);
    if(h >= -5) return QColor(206, 255, 249);
    if(h >= -10) return QColor(176, 255, 249);
    if(h >= -20) return QColor(152, 251, 255);
    if(h >= -30) return QColor(126, 242, 255);
    if(h >= -40) return QColor(129, 219, 253);
    if(h >= -50) return QColor(100, 194, 255);
    if(h >= -60) return QColor(88, 165, 253);
    if(h <= -80) return QColor(70, 138, 249);
}

Painter::Painter(QObject *parent) : QObject(parent)
{

}

Painter::Painter(QLabel *l)
{
    canvas = l;

    pixmap = new QPixmap(canvas->width(), canvas->height());
    painter = new QPainter(pixmap);

    size = canvas->width();
    canvas_pixmap.resize(size);
    for(int i = 0; i < size; i++)
        canvas_pixmap[i].resize(size);

    init_canvas();
}

void Painter::save_as()
{
    QString strFilter="*.jpeg";
    QString str = QFileDialog::getSaveFileName(0,
                                    "Сохранить изображение",
                                    "D:\\image.jpeg",
                                    "*.png ;; *.jpg ;; *.bmp ;; *.jpeg",
                                    &strFilter
                                    );

    if (!str.isEmpty()) {
        if (strFilter.contains("jpg")){
            pixmap->save(str, "JPG");
        }
        else
            if (strFilter.contains("bmp")){
                 pixmap->save(str, "BMP");
        }
        else
            if(strFilter.contains("png")){
                pixmap->save(str, "PNG");
        }
        else
            if(strFilter.contains(".jpeg")){
                pixmap->save(str, "JPEG");
        }
    }
}

void Painter::draw()
{
    init_canvas();

    for(int l = size - 1; l > 0; l /= 2){
        srand(QTime::currentTime().msec());
        for(int x = 0; x < size - 1; x += l){
            for(int y = 0; y < size - 1; y += l){
                diamond_square(x, y, x + l, y + l);
                //square(x, y, x + l, y + l);
            }
        }
        /*
        for(int x = 0; x < size - 1; x += l){
            for(int y = 0; y < size - 1; y += l){
                //diamond(x, y, x + l, y + l);
            }
        }
        */
    }

    QColor color;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            color = color_by_height(canvas_pixmap[i][j]);
            painter->setPen(color);
            painter->drawPoint(QPoint(i, j));
        }       
    }
    canvas->setPixmap(*pixmap);
}

void Painter::slot_draw()
{
    clear_canvas();
    draw();
}

void Painter::slot_set_r(double val)
{
    r = val;
}

void Painter::slot_save_as()
{
    save_as();
}
