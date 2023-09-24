#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include "figure.h"
#include <QGraphicsScene>
#include <QGraphicsItem>

namespace Ui {
class Canvas;
}

class Line : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    static const int FONT_SIZE;
    static const int VERTEX_RADIUS;

public:
    explicit Line(int x1, int y1, int x2, int y2) : _x1(x1), _y1(y1), _x2(x2), _y2(y2) {}
    ~Line() {}

private:
    QRectF boundingRect() const {
        return QRectF(QPointF(_x1, _y1), QPointF(_x2, _y2));
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
    {
        painter->setBrush(QBrush(QColor(64, 169, 201)));
        painter->drawLine(QPointF(_x1, _y1), QPointF(_x2, _y2));
    }


private:
    int _x1;
    int _y1;
    int _x2;
    int _y2;
};

class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();
    void DrawFigure(const Figure& figure);
    void DrawLines(const std::vector<std::pair<int, int>>& arr);
    void setPen(const QPen& pen) { _pen = pen; }
    void Rotation(int angle);
    void DrawItem(QGraphicsItem* item);
    void DrawSline(std::vector<QGraphicsItem*> items);
    void Clear();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::Canvas *ui;
    Figure _cur_figure;
    QPen _pen;
    double _zoom;

    std::vector<Line*> _lines;
    QGraphicsScene* _scene;
};

#endif // CANVAS_H
