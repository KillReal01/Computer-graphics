#ifndef ARRAY_H
#define ARRAY_H

#include <QGraphicsItem>
#include <QLineF>
#include <QPainter>

class Array : public QGraphicsItem
{
public:
    Array(QPointF start, QPointF finish);

private:
    /*brief Получение рабочей области QGraphicsItem*/
    QRectF boundingRect() const;

    /*brief Отрисовка QGraphicsItem*/
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QLineF line_;
};

#endif // ARRAY_H
