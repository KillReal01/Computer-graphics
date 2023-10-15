#include "array.h"

Array::Array(QPointF start, QPointF finish)
{
    line_ = QLineF(start, finish);
}


QRectF Array::boundingRect() const
{
    return QRectF(line_.x1(), line_.y1(), line_.x2(), line_.y2());
}

void Array::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawLine(line_);
}
