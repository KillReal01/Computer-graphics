#include "figure.h"
#include "matrix.h"
#include "convert.h"
#include <vector>


Figure::Figure() {}


Figure::Figure(const std::vector<Edge<Point>>& data) : data(data) {}


std::vector<Edge<Point>> Figure::getPerspective(int axe) const
{
    std::vector<Edge<Point>> res;
    for (const auto& edge : data){
        Point start = convertTo2d(edge.getStart(), axe);
        Point end = convertTo2d(edge.getEnd(), axe);
        Edge<Point> e(start, end);
        res.push_back(e);
    }
    return res;
}

void Figure::convertFigure(const Matrix<double>& mtx)
{
    for(auto& edge : data){
        Matrix<double> start(edge.getStart().getData());
        Matrix<double> end(edge.getEnd().getData());

        start = start * mtx;
        end = end * mtx;

        Point s(start.getMatrix()[0]);
        Point e(end.getMatrix()[0]);

        edge = Edge<Point>(s, e);
    }
}


void Figure::rotationOX(int angle)
{
    Matrix<double> rotate = rotationMatrixOX(angle);
    convertFigure(rotate);
}

void Figure::rotationOY(int angle)
{
    Matrix<double> rotate = rotationMatrixOY(angle);
    convertFigure(rotate);
}

void Figure::rotationOZ(int angle)
{
    Matrix<double> rotate = rotationMatrixOZ(angle);
    convertFigure(rotate);
}




