#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include "figure.h"


class Canvas : public QWidget
{
public:
    explicit Canvas(QWidget *parent = nullptr);

private:
    Figure* figure;

    void paintEvent(QPaintEvent*);
};

#endif // CANVAS_H
