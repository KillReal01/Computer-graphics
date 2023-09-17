#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <QString>

template<class T>
class Matrix
{
public:
    Matrix();
    Matrix(int, int);

    Matrix(const Matrix<T> &);
    Matrix(int, int, T**);

    Matrix(const std::vector<T>&);
    Matrix(const std::vector<std::vector<T>>&);

    ~Matrix();

    void set();
    void transpose();

    Matrix<T> operator* (const Matrix<T>& other);
    Matrix<T>& operator= (const Matrix<T>& other);

    //template<class T>
    friend std::ostream &operator<<(std::ostream &, Matrix<T> &);

    //template<class T>
    friend QString &operator<<(QString &s, Matrix<T> &c);

private:
    int col;
    int row;
    T ** mtx;

    T ** allocate_memory(int, int);
    void clear();
};


template<class T>
Matrix<T>::Matrix() { }

template<class T>
Matrix<T>::Matrix(int n, int m) {
    this->row = n;
    this->col = m;
    this->mtx = this->allocate_memory(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            this->mtx[i][j] = T(0);
        }
    }
}


template<class T>
Matrix<T>::Matrix(const Matrix<T>& other)
{
    this->row = other.row;
    this->col = other.col;
    this->mtx = this->allocate_memory(this->row, this->col);
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->col; j++) {
            this->mtx[i][j] = other.mtx[i][j];
        }
    }
}

template<class T>
Matrix<T>::Matrix(int n, int m, T ** mtx)
{
    this->row = n;
    this->col = m;
    this->mtx = this->allocate_memory(this->row, this->col);
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->col; j++) {
            this->mtx[i][j] = mtx[i][j];
        }
    }
}


template<class T>
Matrix<T>::Matrix(const std::vector<T> &vec)
{
    this->row = 1;
    this->col = vec.size();
    this->mtx = this->allocate_memory(this->row, this->col);

    for (int j = 0; j < this->col; j++) {
        this->mtx[0][j] = vec[j];
    }
}


template<class T>
Matrix<T>::Matrix(const std::vector<std::vector<T> > & vec)
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
void Matrix<T>::set() {
    this->clear();

    std::cout << "Enter rows: ";
    std::cin >> this->row;

    std::cout << "Enter cols: ";
    std::cin >> this->col;

    std::cout << "Enter matrix:\n";

    mtx = this->allocate_memory(this->row, this->col);
    for (int i = 0; i < this->row; i++) {
        for (int j = 0; j < this->col; j++) {
            std::cin >> mtx[i][j];
        }
    }
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
Matrix<T> Matrix<T>::operator*(const Matrix<T> &other)
{
    int m = this->row;
    int n = other.col;
    int k = this->col;
    Matrix tmp(m, n);

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
           tmp.mtx[i][j] = 0;
           for (int p = 0; p < k; p++){
              tmp.mtx[i][j] += this->mtx[i][p] * other.mtx[p][j];
           }
       }
    }
    return tmp;
}

template<class T>
Matrix<T> &Matrix<T>::operator=(const Matrix<T> &other)
{
    if (this != &other){
        this->clear();
        this->row = other.row;
        this->col = other.col;

        this->mtx = this->allocate_memory(this->row, this->col);
        for (int i = 0; i < this->row; i++) {
            for (int j = 0; j < this->col; j++) {
                this->mtx[j][i] = other.mtx[i][j];
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

template<class T>
QString& operator<<(QString& s, Matrix<T>& c)
{
    int n = c.row;
    int m = c.col;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            s << c.mtx[i][j];
        }
    }
    return s;
}


#endif // MATRIX_H
