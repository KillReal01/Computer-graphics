#ifndef FIGURE_H
#define FIGURE_H

#include "structure.h"
#include <vector>
#include <QPainter>


class Figure
{
public:
    Figure();
    explicit Figure(const std::vector<Edge3d>& data);

    std::vector<Edge2d> getPerspective();
    void draw(QPainter *p);
    void rotation(int);
    QColor getColor() const;

private:
    std::vector<Edge3d> data;
    QColor color;
};

#endif // FIGURE_H
