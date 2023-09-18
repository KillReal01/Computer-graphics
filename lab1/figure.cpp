#define _USE_MATH_DEFINES

#include "figure.h"
#include "matrix.h"

#include <vector>
#include <cmath>

namespace {
    double angleToRadian(int angle){
        return (angle * M_PI) / 180;
    }

    Matrix<double> createRotationMatrix3d(int angle) {
        double tmp = angleToRadian(angle);
        std::vector<std::vector<double>> vec{
            {cos(tmp), -sin(tmp), 0},
            {sin(tmp), cos(tmp), 0},
            {0, 0, 1}
        };
        Matrix<double> mtx(vec);
        return mtx;
    }

    Point2d convertTo2d(Point3d& v) {
        int angle = 20;
        double value = sin(angleToRadian(angle));
        int sign = v.y ? -1 : 1;
        return Point2d(v.x + value * sign * v.y, v.z + value * sign * v.y);
    }
}


Figure::Figure() {}


Figure::Figure(const std::vector<Edge<Point3d>>& data) : data(data) {}


std::vector<Edge<Point2d>> Figure::getPerspective()
{
    std::vector<Edge<Point2d>> res;
    res.reserve(data.size());
    for (auto& edge : data) {
        Point2d start = convertTo2d(edge.start);
        Point2d end = convertTo2d(edge.end);
        Edge<Point2d> e(start, end);
        res.push_back(e);
    }
    return res;
}


void Figure::rotation(int angle)
{
    Matrix<double> rotate = createRotationMatrix3d(angle);
    for (auto& edge3d : data){
        Point3d start = edge3d.getStartVector();
        Point3d end = edge3d.getEndVector();

        Matrix<double> a(start.getVectorFromPoint());
        Matrix<double> b(end.getVectorFromPoint());

        a = a * rotate;
        b = b * rotate;

        auto tmp = a.getVector();
        start = Point3d(tmp[0], tmp[1], tmp[2]);
        edge3d.setStartVector(start);

        tmp = b.getVector();
        end = Point3d(tmp[0], tmp[1], tmp[2]);
        edge3d.setEndVector(end);
    }
}


