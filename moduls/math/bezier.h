#ifndef BEZIER_H
#define BEZIER_H

#include "matrix.h"
#include "point.h"
#include <vector>
#include <QtMath>

namespace{
    /* brief Число сочетаний из n по k
     *
     * param n - размерность множетсва
     * param k - размерность подмножетсва
     *
     * return Число сочетаний из n по k
     */
    unsigned long long C(int n, int k) {
        if (k < 0 || k > n) {
            return 0;
        }

        unsigned long long result = 1;

        for (int i = 0; i < k; ++i) {
            result *= (n - i);
            result /= (i + 1);
        }

        return result;
    }

    /* brief Функция Бернштайна
     *
     * param u - основание базиса
     * param i - размерность подмножетсва
     * param n - размерность базиса
     *
     * return Функция Бернштайна
     */
    double Bernshtain(int n, int i, double u) {
        unsigned long long result = C(n, i);
        double tmp = qPow(u, i) * qPow((1 - u), (n - i));
        return result * tmp;
    }

    /* brief Точка Безье
     *
     * param u - основание базиса
     * param u - основание базиса
     * param mtx - Матрица опорных точек
     *
     * return Точка Безье
     */
    Point bezierPoint(double u, double w, Matrix<Point>& mtx){
        int n = mtx.getRow() - 1;
        int m = mtx.getColumn() - 1;
        Point res{};
        for (int i = 0; i < n + 1; ++i){
            for (int j = 0; j < m + 1; ++j){
                Point tmp = mtx[i][j];
                res = res + Bernshtain(n, i, u) * Bernshtain(m, j, w) * tmp;
            }
        }
        return res;
    }


    /* brief Поверхность Безье
     *
     * param step - шаг прохода
     * param mtx - Матрица опорных точек
     *
     * return Поверхность Безье
     */
    Matrix<Point> createBezierSurface(double num, Matrix<Point>& mtx){
        int size_u = num;
        int size_w = num;
        Matrix<Point> P(size_u, size_w);
        for (int i = 0; i < size_u; ++i){
            for (int j = 0; j <size_w; ++j){
                double u = i * 1.0 / (size_u - 1);
                double w = j * 1.0 / (size_w - 1);
                Point tmp = bezierPoint(u, w, mtx);
                P[i][j] = tmp;
            }
        }
        return P;
    }

}
#endif // BEZIER_H
