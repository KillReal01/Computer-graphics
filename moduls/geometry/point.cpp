#include "point.h"
#include <algorithm>


Point::Point()
{
    data = std::vector<double>{0, 0, 0, 1};
}

Point::Point(double x, double y, double z)
{
    data = std::vector<double>{x, y, z, 1};
}

Point::Point(double x, double y, double z, double h)
{
    data = std::vector<double>{x, y, z, h};
}

Point::Point(const std::vector<double> &vec)
{
    data = std::vector<double>(4);
    int min = vec.size() < 4 ? vec.size() : 4;
    for(int i = 0; i < min; ++i){
        data[i] = vec[i];
    }
}

Point::Point(const Point &other) {
    data = other.data;
}

Point &Point::operator=(const Point &other) {
    if (this == &other) {
        return *this;
    }
    data = other.data;
    return *this;
}


std::vector<double> Point::getData() const {
    return data;
}

void Point::scale()
{
    for (auto& coord : data) {
        coord /= data[3];
    }
}

const Point operator*(double n, const Point &point) {
    Point result(point);
    result.data[0] *= n;
    result.data[1] *= n;
    result.data[2] *= n;
    return result;
}

const Point Point::operator*(double n) const {
    Point result(*this);
    result.data[0] *= n;
    result.data[1] *= n;
    result.data[2] *= n;
    return result;
}

const Point Point::operator+(const Point &p){
    Point result(*this);
    result.data[0] += p.data[0];
    result.data[1] += p.data[1];
    result.data[2] += p.data[2];
    return result;
}

const Point Point::operator-(const Point &p){
    Point result(*this);
    result.data[0] -= p.data[0];
    result.data[1] -= p.data[1];
    result.data[2] -= p.data[2];
    return result;
}

double Point::operator[](int index){
    return data.at(index);
}

float Point::x() const
{
    if (data.size() > 0)
        return data[0];
    else return {};
}

float Point::y() const
{
    if (data.size() > 1)
        return data[1];
    else return {};
}

float Point::z() const
{
    if (data.size() > 2)
        return data[2];
    else return {};
}

float Point::h() const
{
    if (data.size() > 3)
        return data[3];
    else return {};
}

std::ostream &operator<<(std::ostream &os, const Point &p){
    os << "(" << p.data[0] << ";" << p.data[1] << ";" << p.data[2] << ")";
    return os;
}


