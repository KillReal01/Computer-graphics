﻿#ifndef TVERTEX_H
#define TVERTEX_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

class TVertex : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    static const int FONT_SIZE;
    static const int VERTEX_RADIUS;

public:
    explicit TVertex(QString name, QObject *parent = nullptr);
    const QString& Name() const;
    QRectF Rect() const;
    ~TVertex();

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QString _Name;
    QRectF _Rect;

signals:
    void move();
};

#endif // TVERTEX_H
