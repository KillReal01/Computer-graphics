#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include "figure.h"

namespace Ui {
class Canvas;
}

class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();
    void DrawFigure(const Figure& figure);
    void setPen(const QPen& pen) { _pen = pen; }
    void Rotation(int angle);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::Canvas *ui;
    Figure _cur_figure;
    QPen _pen;
    double _zoom;
};

#endif // CANVAS_H
