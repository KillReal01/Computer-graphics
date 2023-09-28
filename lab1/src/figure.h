#ifndef FIGURE_H
#define FIGURE_H

#include "structure.h"
#include <vector>


class Figure
{
public:
    Figure();
    explicit Figure(const std::vector<Edge<Point3d>>& data);

    std::vector<Edge<Point2d>> getPerspective() const;
    std::vector<Edge<Point3d>> getData() const;
    void rotation(int, int);

private:
    std::vector<Edge<Point3d>> data;
};

#endif // FIGURE_H
