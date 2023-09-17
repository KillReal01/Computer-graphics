#include "figure.h"
#include "matrix.h"
#include <vector>
#include <cmath>


namespace  {
    Matrix<double> createRotationMatrix3d(int angle){
        double tmp = angle * 180 * M_1_PI;
        std::vector<std::vector<double>> vec{
            {cos(tmp), -sin(tmp), 0},
            {sin(tmp), cos(tmp), 0},
            {0, 0, 1}
        };
        Matrix<double> mtx(vec);
        return mtx;
    }

    Point2d convertTo2d(Point3d& v) {
        int sign = v.y ? -1 : 1;
        return Point2d(v.x + 0.7 * sign * v.y, v.z + 0.7 * sign * v.y);
    }
}


Figure::Figure() {}


Figure::Figure(const std::vector<Edge3d> &data) : data(data){}


std::vector<Edge2d> Figure::getPerspective()
{
    std::vector<Edge2d> res(data.size());
    for (auto & edge : data){
        Point2d start = convertTo2d(edge.start);
        Point2d end = convertTo2d(edge.start);
        Edge2d e(start, end);
        res.push_back(e);
    }
    return res;
}


void Figure::draw(QPainter *p){}


void Figure::rotation(int angle)
{
    Matrix<double> rotate = createRotationMatrix3d(angle);
    for (int i = 0; i < data.size(); ++i){
        Point3d start = data[i].getStartVector();
        Point3d end = data[i].getEndVector();

        Matrix<double> a(start.getVectorFromPoint());
        Matrix<double> b(end.getVectorFromPoint());

        a = a * rotate;
        b = b * rotate;

        auto tmp = a.getVector();
        start = Point3d(tmp[0], tmp[1], tmp[2]);
        data[i].setStartVector(start);

        tmp = b.getVector();
        end = Point3d(tmp[0], tmp[1], tmp[2]);
        data[i].setEndVector(end);
    }
}


QColor Figure::getColor() const
{
    return this->color;
}

