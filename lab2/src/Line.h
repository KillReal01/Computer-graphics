#ifndef TLINE_H
#define TLINE_H

#include <QObject>
#include <QWidget>
#include <QGraphicsItem>
#include <QPainter>

class Line : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    static const int FONT_SIZE;
    static const int VERTEX_RADIUS;

public:
    Line(int x1, int y1, int x2, int y2) : _x1(x1), _y1(y1), _x2(x2), _y2(y2), curve(false) {}
    Line(int x1, int y1, int x2, int y2, bool type) : _x1(x1), _y1(y1), _x2(x2), _y2(y2), curve(type) {}
    ~Line() {}

private:
    QRectF boundingRect() const {
        return QRectF(QPointF(_x1, _y1), QPointF(_x2, _y2));
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
    {
        if (curve)
            painter->setPen(QPen(Qt::red, 2, Qt::SolidLine));
        else
            painter->setPen(QPen(Qt::black, 2, Qt::DotLine));
        painter->drawLine(QPointF(_x1, _y1), QPointF(_x2, _y2));
    }


private:
    int _x1;
    int _y1;
    int _x2;
    int _y2;
    bool curve; /* line style*/
};

#endif // TLINE_H
