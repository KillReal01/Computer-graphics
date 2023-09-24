#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <vector>

struct Point3d
{
    double x;
    double y;
    double z;

    Point3d() : x(0), y(0), z(0) {};
    Point3d(double x, double y, double z) : x(x), y(y), z(z) {}
    std::vector<double> getVectorFromPoint() const {
        return std::vector<double>{x, y, z};
    }
};

struct Point2d
{
    double x;
    double y;

    Point2d() : x(0), y(0) {};
    Point2d(double x, double y) : x(x), y(y) {}
    std::vector<double> getVectorFromPoint() const {
        return std::vector<double>{x, y};
    }
};


template<class T>
struct Edge
{
public:
    T start;
    T end;

    Edge() {}
    Edge(const T& start, const T& end) : start(start), end(end) {}

    void setStartVector(const T& p) {
        this->start = p;
    }

    void setEndVector(const T& p) {
        this->end = p;
    }

    T getStartVector() const {
        return start;
    }

    T getEndVector() const {
        return end;
    }

};

#endif // STRUCTURE_H
