#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <vector>

struct Point3d
{
    double x;
    double y;
    double z;

    Point3d() : x(0), y(0), z(0){};
    Point3d(double x, double y, double z): x(x), y(y), z(z){}
    std::vector<double> getVectorFromPoint() const{
        return std::vector<double>{x, y, z};
    }
};

struct Point2d
{
    double x;
    double y;

    Point2d() : x(0), y(0){};
    Point2d(double x, double y): x(x), y(y) {}
    std::vector<double> getVectorFromPoint() const{
        return std::vector<double>{x, y};
    }
};

struct Edge3d
{
public:
    Point3d start;
    Point3d end;

    Edge3d(){}
    Edge3d(const Point3d& start, const Point3d& end) : start(start), end(end){}

    void setStartVector(const Point3d& p){
        this->start = p;
    }

    void setEndVector(const Point3d& p){
        this->end = p;
    }

    Point3d getStartVector() const{
        return start;
    }

    Point3d getEndVector() const{
        return end;
    }

};

struct Edge2d{
public:
    Point2d start;
    Point2d end;

    Edge2d(){}
    Edge2d(const Point2d& start, const Point2d& end) : start(start), end(end){}

    void setStartVector(const Point2d& p){
        this->start = p;
    }

    void setEndVector(const Point2d& p){
        this->end = p;
    }

    Point2d getStartVector() const{
        return start;
    }

    Point2d getEndVector() const{
        return end;
    }
};

#endif // STRUCTURE_H
