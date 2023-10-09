#ifndef BEZIER_H
#define BEZIER_H

#include "matrix.h"
#include "structure.h"
#include <vector>
#include <QtMath>

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

Matrix<double> bezierBasis(double u, int n){
    std::vector<double> vec(n + 1);
    for (int i = 0; i < vec.size(); ++i){
        vec[i] = qPow(u, n - i);
    }
    Matrix<double> mtx(vec);
    return mtx;
}


Matrix<double> binomialMatrix(int n){
    Matrix<double> mtx(n + 1, n + 1);
    for (int i = 0; i < mtx.getRow(); ++i){
        for (int j = 0; j < mtx.getColumn(); ++j){
            int tmp = n - j - i;
            if (tmp < 0)
                mtx[i][j] = 0;
            else
                mtx[i][j] = C(n, j) * C(n - j, tmp) * qPow(-1, n - i - j);
        }
    }
    return mtx;
}

#endif // BEZIER_H
