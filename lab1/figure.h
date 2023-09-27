#ifndef FIGURE_H
#define FIGURE_H

#include "structure.h"
#include <vector>


class Figure
{
public:
    Figure();
    Figure(const std::vector<Edge<Point3d>>& data);
    Figure(const Figure&);

    std::vector<Edge<Point3d>> getData() const;
    std::vector<Edge<Point2d>> getPerspective();
    void rotation(int, int);

private:
    std::vector<Edge<Point3d>> data;
};

#endif // FIGURE_H
