#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <ostream>
#include <vector>


struct Point3d
{
    double x;
    double y;
    double z;

    Point3d() : x(0), y(0), z(0) {};
    Point3d(double x, double y, double z) : x(x), y(y), z(z) {}
    Point3d& operator=(const Point3d& other) {
        if (this == &other) {
            return *this;  // Проверка на самоприсваивание
        }
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    Point3d(const Point3d& other) {
        x = other.x;
        y = other.y;
        z = other.z;
    }
    std::vector<double> getVectorFromPoint() const {
        return std::vector<double>{x, y, z};
    }

    friend const Point3d operator*(double n, const Point3d& point) {
        Point3d result(point);
        result.x *= n;
        result.y *= n;
        result.z *= n;
        return result;
    }

    Point3d operator*(double n) const {
        Point3d result(*this);
        result.x *= n;
        result.y *= n;
        result.z *= n;
        return result;
    }

    Point3d operator+ (const Point3d & p){
        Point3d t(*this);
        t.x += p.x;
        t.y += p.y;
        t.z += p.z;
        return t;
    }

    Point3d operator- (const Point3d & p){
        Point3d t(*this);
        t.x -= p.x;
        t.y -= p.y;
        t.z -= p.z;
        return t;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point3d& p){
        os << "(" << p.x << ";" << p.y << ";" << p.z << ")";
        return os;
    }
};

struct Point2d
{
    double x;
    double y;

    Point2d() : x(0), y(0) {};
    Point2d(double x, double y) : x(x), y(y) {}
    Point2d& operator=(const Point2d& other) {
        if (this == &other) {
            return *this;  // Проверка на самоприсваивание
        }
        x = other.x;
        y = other.y;
        return *this;
    }

    Point2d(const Point2d& other) {
        x = other.x;
        y = other.y;
    }

    std::vector<double> getVectorFromPoint() const {
        return std::vector<double>{x, y};
    }

    friend const Point2d operator*(double n, const Point2d& point) {
        Point2d result(point);
        result.x *= n;
        result.y *= n;
        return result;
    }

    Point2d operator*(int n){
        Point2d t(*this);
        t.x *= n;
        t.y *= n;
        return t;
    }

    Point2d operator+ (const Point2d & p){
        Point2d t(*this);
        t.x += p.x;
        t.y += p.y;
        return t;
    }

    Point2d operator- (const Point2d & p){
        Point2d t(*this);
        t.x -= p.x;
        t.y -= p.y;
        return t;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point2d& p){
        os << "(" << p.x << ";" << p.y << ")";
        return os;
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
