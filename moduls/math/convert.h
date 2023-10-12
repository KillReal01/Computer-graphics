#ifndef CONVERT_H
#define CONVERT_H

#include "point.h"
#include "matrix.h"
#include <cmath>

namespace{
    /* brief Преобразование угла из радиан в градусы
     *
     * param angle - угол
     *
     * return Угол в градусах
     */
    double radianToAngle(int radian){
        return (radian * M_PI) / 180;
    }


    /* brief Матрица поворота по оси OX
     *
     * param angle - угол
     *
     * return Матрица преобразования
     */
    Matrix<double> rotationMatrixOX(int angle) {
        double tmp = radianToAngle(angle);
        std::vector<std::vector<double>> vec{
            {1, 0, 0, 0},
            {0, cos(tmp), -sin(tmp), 0},
            {0, sin(tmp), cos(tmp), 0},
            {0, 0, 0, 1}
        };
        Matrix<double> mtx(vec);
        return mtx;
    }


    /* brief Матрица поворота по оси OY
     *
     * param angle - угол
     *
     * return Матрица преобразования
     */
    Matrix<double> rotationMatrixOY(int angle) {
        double tmp = radianToAngle(angle);
        std::vector<std::vector<double>> vec{
            {cos(tmp), 0, sin(tmp), 0},
            {0, 1, 0, 0},
            {-sin(tmp), 0, cos(tmp), 0},
            {0, 0, 0, 1}
        };
        Matrix<double> mtx(vec);
        return mtx;
    }


    /* brief Матрица поворота по оси OZ
     *
     * param angle - угол
     *
     * return Матрица преобразования
     */
    Matrix<double> rotationMatrixOZ(int angle) {
        double tmp = radianToAngle(angle);
        std::vector<std::vector<double>> vec{
            {cos(tmp), -sin(tmp), 0, 0},
            {sin(tmp), cos(tmp), 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        };
        Matrix<double> mtx(vec);
        return mtx;
    }


    /* brief Преобразование точки в 2d
     *
     * param point - 3d точка
     * param index - индекс пространства, которое убираем
     *
     * return 2d точка
     */
    Point convertTo2d(const Point& point, int index) {
        std::vector<double> tmp(point.getData());
        tmp[index] = 0;
        return Point(tmp);
    }
}

#endif // CONVERT_H
