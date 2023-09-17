#include "canvas.h"
#include <QPainter>

Canvas::Canvas(QWidget *parent)
    : QWidget{parent}
{
    setFixedSize(500, 500);
    setStyleSheet("background-color: white;");

    //инициализация фигуры
}

void Canvas::paintEvent(QPaintEvent*)
{
    QPainter p;
    p.begin(this);
    //figure->draw(&p);
    p.end();
}
