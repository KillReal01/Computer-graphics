#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
//#include <QString>

template<class T>
class Matrix
{
public:
    Matrix();
    Matrix(int, int);

    Matrix(const Matrix<T>&);
    Matrix(int, int, T**);

    Matrix(const std::vector<T>&);
    Matrix(const std::vector<std::vector<T>>&);

    ~Matrix();

    void transpose();
    void setValue(int, int, T);
    std::vector<T> getVector() const;
    std::vector<std::vector<T>> getVectors() const;

    Matrix<T> operator* (const Matrix<T>&);
    Matrix<T> operator+ (const Matrix<T>&);
    Matrix<T> operator- (const Matrix<T>&);
    Matrix<T>& operator= (const Matrix<T>&);
    bool operator== (const Matrix<T>&) const;

    template<class N>
    friend std::ostream& operator<<(std::ostream&, Matrix<N>&);

    //template<class N>
    //friend QString& operator<<(QString& s, Matrix<N>& c);

private:
    int col;
    int row;
    T** mtx;

    T** allocate_memory(int, int);
    void clear();
};


template<class T>
Matrix<T>::Matrix() : row(0), col(0), mtx(nullptr) { }

template<class T>
Matrix<T>::Matrix(int n, int m) : row(n), col(m) {
    this->mtx = this->allocate_memory(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            this->mtx[i][j] = T(0);
        }
    }
}


template<class T>
Matrix<T>::Matrix(const Matrix<T>& other) : row(other.row), col(other.col)
{
    this->mtx = this->allocate_memory(this->row, this->col);
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->col; j++) {
            this->mtx[i][j] = other.mtx[i][j];
        }
    }
}

template<class T>
Matrix<T>::Matrix(int n, int m, T** mtx) : row(n), col(m)
{
    this->mtx = this->allocate_memory(this->row, this->col);
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->col; j++) {
            this->mtx[i][j] = mtx[i][j];
        }
    }
}


template<class T>
Matrix<T>::Matrix(const std::vector<T>& vec)
{
    this->row = 1;
    this->col = vec.size();
    this->mtx = this->allocate_memory(this->row, this->col);

    for (int j = 0; j < this->col; j++) {
        this->mtx[0][j] = vec[j];
    }
}


template<class T>
Matrix<T>::Matrix(const std::vector<std::vector<T>>& vec)
{
    this->row = vec.size();
    this->col = vec[0].size();
    this->mtx = this->allocate_memory(this->row, this->col);
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->col; j++) {
            this->mtx[i][j] = vec[i][j];
        }
    }
}


template<class T>
T** Matrix<T>::allocate_memory(int n, int m) {
    T** tmp = new T * [n];
    for (int i = 0; i < n; i++) {
        tmp[i] = new T[m];
    }
    return tmp;
}


template<class T>
Matrix<T>::~Matrix() {
    this->clear();
}


template<class T>
void Matrix<T>::clear() {
    for (int i = 0; i < this->row; i++) {
        delete[] this->mtx[i];
    }
    delete[] this->mtx;
}



template<class T>
void Matrix<T>::transpose() {
    T** tmp = this->allocate_memory(this->col, this->row);
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->col; j++) {
            tmp[j][i] = this->mtx[i][j];
        }
    }
    this->clear();
    this->mtx = tmp;
    std::swap(this->row, this->col);
}

template<class T>
void Matrix<T>::setValue(int i, int j, T value) {
    if (i >= 0 && i < this->row && j >= 0 && j < this->col)
        this->mtx[i][j] = value;
}

// Только для матрицы 1 * n
template<class T>
std::vector<T> Matrix<T>::getVector() const
{
    if (this->row > 1)
        return {};

    std::vector<T> vec(this->col);
    for (int i = 0; i < this->col; ++i) {
        vec.push_back(this->mtx[0][i]);
    }
    return vec;
}


template<class T>
std::vector<std::vector<T>> Matrix<T>::getVectors() const
{
    std::vector<std::vector<T>> vec(this->row, std::vector<T>(this->col));
    for (int i = 0; i < this->row; ++i) {
        for (int j = 0; j < this->col; ++j) {
            vec[i][j] = this->mtx[i][j];
        }
    }
    return vec;
}

template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other)
{
    int m = this->row;
    int n = other.col;
    int k = this->col;
    Matrix tmp(m, n);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            tmp.mtx[i][j] = 0;
            for (int p = 0; p < k; p++) {
                tmp.mtx[i][j] += this->mtx[i][p] * other.mtx[p][j];
            }
        }
    }
    return tmp;
}

template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other)
{
    int m = this->row;
    int n = this->col;
    Matrix tmp(m, n);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            tmp.mtx[i][j] = this->mtx[i][j] + other.mtx[i][j];
        }
    }
    return tmp;
}

template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& other)
{
    int m = this->row;
    int n = this->col;
    Matrix tmp(m, n);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            tmp.mtx[i][j] = this->mtx[i][j] - other.mtx[i][j];
        }
    }
    return tmp;
}

template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other)
{
    if (this != &other) {
        this->clear();
        this->row = other.row;
        this->col = other.col;

        this->mtx = this->allocate_memory(this->row, this->col);
        for (int i = 0; i < this->row; i++) {
            for (int j = 0; j < this->col; j++) {
                this->mtx[i][j] = other.mtx[i][j];
            }
        }
    }
    return *this;
}


template<class T>
std::ostream& operator<<(std::ostream& os, Matrix<T>& a) {
    for (int i = 0; i < a.row; i++) {
        for (int j = 0; j < a.col; j++) {
            os << a.mtx[i][j] << " ";
        }
        os << "\n";
    }
    return os;
}

template <class T>
bool Matrix<T>::operator== (const Matrix<T>& other) const{
    if (this->row != other.row || this->col != other.col)
        return false;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (this->mtx[i][j] != other.mtx[i][j])
                return false;
        }
    }
    return true;
}


//template<class T>
//QString& operator<<(QString& s, Matrix<T>& c)
//{
//    int n = c.row;
//    int m = c.col;
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < m; j++) {
//            s << c.mtx[i][j];
//        }
//    }
//    return s;
//}


#endif // MATRIX_H
