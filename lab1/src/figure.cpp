#define _USE_MATH_DEFINES

#include "figure.h"
#include "matrix.h"
#include "direction.h"

#include <vector>
#include <cmath>

namespace {
    double radianToAngle(int radian){
        return (radian * M_PI) / 180;
    }

    Matrix<double> rotationOX(int angle) {
        double tmp = radianToAngle(angle);
        std::vector<std::vector<double>> vec{
            {1, 0, 0},
            {0, cos(tmp), -sin(tmp)},
            {0, sin(tmp), cos(tmp)}
        };
        Matrix<double> mtx(vec);
        return mtx;
    }

    Matrix<double> rotationOY(int angle) {
        double tmp = radianToAngle(angle);
        std::vector<std::vector<double>> vec{
            {cos(tmp), 0, sin(tmp)},
            {0, 1, 0},
            {-sin(tmp), 0, cos(tmp)}
        };
        Matrix<double> mtx(vec);
        return mtx;
    }

    Matrix<double> rotationOZ(int angle) {
        double tmp = radianToAngle(angle);
        std::vector<std::vector<double>> vec{
            {cos(tmp), -sin(tmp), 0},
            {sin(tmp), cos(tmp), 0},
            {0, 0, 1}
        };
        Matrix<double> mtx(vec);
        return mtx;
    }

    Point2d convertTo2d(const Point3d& v) {
        Matrix<double> tmp(v.getVectorFromPoint());
        tmp = tmp * rotationOX(10);
        std::vector<double> vec = tmp.getVector();
        Point3d np{vec[0], vec[1], vec[2]};
        return Point2d(np.x, np.z);
    }
}


Figure::Figure() {}


Figure::Figure(const std::vector<Edge<Point3d>>& data) : data(data) {}

std::vector<Edge<Point3d> > Figure::getData() const
{
    return data;
}


std::vector<Edge<Point2d>> Figure::getPerspective() const
{
    std::vector<Edge<Point2d>> res;
    res.reserve(data.size());
    for (const auto& edge : data) {
        Point2d start = convertTo2d(edge.start);
        Point2d end = convertTo2d(edge.end);
        Edge<Point2d> e(start, end);
        res.push_back(e);
    }
    return res;
}


void Figure::rotation(int direction, int angle)
{
    Matrix<double> rotate;
    switch (direction){
        case x:
            rotate = rotationOX(angle);
            break;
        case y:
            rotate = rotationOY(angle);
            break;
        case z:
            rotate = rotationOZ(angle);
            break;
    }


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


