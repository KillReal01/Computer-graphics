#include "figure.h"
#include "matrix.h"
#include "convert.h"
#include <vector>


Figure::Figure() {}

Figure::Figure(const std::vector<Edge<Point>>& data) : data(data) {}

Figure::Figure(const std::vector<Edge<Point> > &data, const Point &c): data(data), center(c) {}

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

void Figure::setCenter(const Point &c){
    center = c;
}


void Figure::rotationOX(int angle)
{
    Matrix<double> rotate = rotationMatrixOX(angle);
    Matrix<double> moveToCenter = moveMatrix(-center[0], -center[1], -center[2]);
    Matrix<double> moveFromCenter = moveMatrix(center[0], center[1], center[2]);
    auto T = moveToCenter * rotate * moveFromCenter;
    convertFigure(T);
}

void Figure::rotationOY(int angle)
{
    Matrix<double> rotate = rotationMatrixOY(angle);
    Matrix<double> moveToCenter = moveMatrix(-center[0], -center[1], -center[2]);
    Matrix<double> moveFromCenter = moveMatrix(center[0], center[1], center[2]);
    auto T = moveToCenter * rotate * moveFromCenter;
    convertFigure(T);
}

void Figure::rotationOZ(int angle)
{
    Matrix<double> rotate = rotationMatrixOZ(angle);
    Matrix<double> moveToCenter = moveMatrix(-center[0], -center[1], -center[2]);
    Matrix<double> moveFromCenter = moveMatrix(center[0], center[1], center[2]);
    auto T = moveToCenter * rotate * moveFromCenter;
    convertFigure(T);
}




