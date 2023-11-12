#ifndef POINT_H
#define POINT_H

#include <vector>
#include <iostream>


class Point
{
public:
    /*brief Конструктор*/
    Point();

    /*brief Конструктор*/
    Point(double x, double y, double z);

    /*brief Конструктор*/
    Point(double x, double y, double z, double h);

    /*brief Конструктор*/
    Point(const std::vector<double>& vec);

    /*brief Конструктор копирования*/
    Point(const Point& other);

    /*brief Оператор =*/
    Point& operator=(const Point& other);

    /*brief Получение точки, как вектор*/
    std::vector<double> getData() const;

    /*brief Оператор * слева */
    friend const Point operator*(double n, const Point& point);

    /*brief Оператор * справа */
    const Point operator*(double n) const;

    /*brief TODO */
    void scale();

    /*brief Оператор + */
    const Point operator+ (const Point & p);

    /*brief Оператор - */
    const Point operator- (const Point & p);

    /*brief Оператор - []*/
    double operator[](int index);

    /*brief Оператор << */
    friend std::ostream& operator<<(std::ostream& os, const Point& p);

    float x() const;

    float y() const;

    float z() const;

    float h() const;

private:
    /*brief Вектор координат */
    std::vector<double> data;
};

#endif // POINT_H
