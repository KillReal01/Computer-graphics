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

    /* brief Матрица перемещения
     *
     * param l, m, n - параметры перемещения
     *
     * return Матрица преобразования
     */
    Matrix<double> moveMatrix(double l, double m, double n) {
        std::vector<std::vector<double>> vec{
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {l, m, n, 1}
        };
        Matrix<double> mtx(vec);
        return mtx;
    }


    /* brief Матрица проекции
     *
     * param o, p, r - параметры проекции
     *
     * return Матрица преобразования
     */
    Matrix<double> projectionMatrix(double o, double p, double r) {
        std::vector<std::vector<double>> vec{
            {1, 0, 0, o},
            {0, 1, 0, p},
            {0, 0, 1, r},
            {0, 0, 0, 1}
        };
        Matrix<double> mtx(vec);
        return mtx;
    }


    /* brief Матрица масштабирования
     *
     * param s - параметры масштабирования
     *
     * return Матрица преобразования
     */
    Matrix<double> scaleMatrix(double s) {
        std::vector<std::vector<double>> vec{
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, s}
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

    Point applyPerspective(const Point &point, float focalLength)
    {
        Matrix<double> perspectiveMatrix = {{
            {focalLength / point.h(), 0, 0, 0},
            {0, focalLength / point.h(), 0, 0},
            {0, 0, 1, 0},
            {0, 0, -1, 0}
        }};
        Matrix<double> pointMatrix(point.getData());

        auto result = pointMatrix * perspectiveMatrix;
        return {result[0][0], result[0][1], result[0][2], result[0][3]};
    }
}

#endif // CONVERT_H
