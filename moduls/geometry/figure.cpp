#include "figure.h"
#include "matrix.h"
#include "convert.h"
#include <vector>


Figure::Figure() {}

Figure::Figure(const std::vector<Edge<Point>>& data) : data(data), center(Point()) {}

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

        auto start2 = start * mtx;
        auto end2 = end * mtx;

        Point s(start2.getMatrix()[0]);
        Point e(end2.getMatrix()[0]);

        //s.scale();
        //e.scale();

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
    convertFigure(rotate);
}

void Figure::rotationOY(int angle)
{
    Matrix<double> rotate = rotationMatrixOY(angle);
    Matrix<double> moveToCenter = moveMatrix(-center[0], -center[1], -center[2]);
    Matrix<double> moveFromCenter = moveMatrix(center[0], center[1], center[2]);
    auto T = moveToCenter * rotate * moveFromCenter;
    convertFigure(rotate);
}

void Figure::rotationOZ(int angle)
{
    Matrix<double> rotate = rotationMatrixOZ(angle);
    Matrix<double> moveToCenter = moveMatrix(-center[0], -center[1], -center[2]);
    Matrix<double> moveFromCenter = moveMatrix(center[0], center[1], center[2]);
    auto T = moveToCenter * rotate * moveFromCenter;
    convertFigure(rotate);
}

QRectF Figure::boundingRect() const {
    if (data.empty())
        return {};
    double max_x, min_x;
    double max_y, min_y;

    QRectF rect;
    max_x = min_x = max_y = min_y = data.front().getEnd().getData()[0];
    for (const auto& edge : data) {
        const auto& point_s = edge.getStart().getData();
        const auto& point_f = edge.getEnd().getData();

        for (const auto& point : {point_s, point_f}) {
            max_x = std::max(max_x, point[0]);
            max_y = std::max(max_y, point[1]);

            min_x = std::min(min_x, point[0]);
            min_y = std::min(min_y, point[1]);
        }
    }
    return QRectF(QPointF(min_x, min_y), QPointF(max_x, max_y));
}

void Figure::paint(QPainter* painter, const QStyleOptionGraphicsItem* /*option*/, QWidget* /*widget*/)
{
    painter->setBrush(QBrush(QColor(64, 169, 201)));
    // const auto perspective = getPerspective(2);
    for (const auto& edge : data) {
        const auto& point_s = edge.getStart().getData();
        const auto& point_f = edge.getEnd().getData();
        painter->drawLine(QLineF(QPointF(point_s[0], point_s[1]), QPointF(point_f[0], point_f[1])));
    }
}



