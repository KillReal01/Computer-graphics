#ifndef CANVAS_H
#define CANVAS_H

#include "Line.h"
#include "direction.h"
#include "figure.h"

#include <QWidget>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsItem>


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
    void DrawLines(const std::vector<std::pair<int, int>>& arr);
    void DrawLines(const std::vector<Line*>& arr);
    void setPen(const QPen& pen) { _pen = pen; }
    void Rotation(int angle);
    void DrawItem(QGraphicsItem* item);
    void DrawText(const QString& text);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::Canvas *ui;
    Figure _cur_figure;
    QPen _pen;
    double _zoom;
    QGraphicsTextItem* _textItem;

    QGraphicsScene* _scene;
};

#endif // CANVAS_H
