#ifndef FIGURE_H
#define FIGURE_H

#include "edge.h"
#include "matrix.h"
#include "point.h"
#include <vector>


class Figure
{
public:
    /*brief Конструктор*/
    Figure();

    /*brief Конструктор*/
    explicit Figure(const std::vector<Edge<Point>>& data);

    /*brief Конструктор*/
    Figure(const std::vector<Edge<Point>>& data, const Point& c);

    /*brief Получение перспективы относительно оси: 0 - OX; 1 - OY; 2 - OZ */
    std::vector<Edge<Point>> getPerspective(int axe) const;

    /*brief Преобразование фигуры по матрице mtx*/
    void convertFigure(const Matrix<double>& mtx);

    /*brief Преобразование фигуры по матрице mtx*/
    void setCenter(const Point& c);

    /*brief Поворот вокруг оси OX*/
    void rotationOX(int);

    /*brief Поворот вокруг оси OY*/
    void rotationOY(int);

    /*brief Поворот вокруг оси OZ*/
    void rotationOZ(int);

private:
    /*brief Вектор ребер(из точек)*/
    std::vector<Edge<Point>> data;

    /*brief Центр фигуры*/
    Point center;
};

#endif // FIGURE_H
