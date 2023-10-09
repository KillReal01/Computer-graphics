#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include "matrix.h"
#include "bezier.h"


//namespace
//{
//    double getPt(int n1, int n2, double perc)
//    {
//        double diff = n2 - n1;
//        return n1 + ( diff * perc );
//    }

//    std::vector<Point2d> getBezierPoint2d(const std::vector<Point2d>& arr, double perc) {
//        if (arr.size() <= 1) {
//            return arr;
//        }
//        std::vector<Point2d> ans;
//        for (int i = 0; i < arr.size() - 1; i++) {
//            const auto& pointA = arr[i];
//            const auto& pointB = arr[i + 1];

//            double x = getPt(pointA.x, pointB.x, perc);
//            double y = getPt(pointA.y, pointB.y, perc);

//            ans.push_back({x, y});
//        }
//        return getBezierPoint2d(ans, perc);
//    }

//    Point3d getBezierPoint3d(const std::vector<Point3d>& arr, double perc) {
//        if (arr.size() <= 1) {
//            return arr[0];
//        }
//        std::vector<Point3d> ans;
//        for (int i = 0; i < arr.size() - 1; i++) {
//            const auto& pointA = arr[i];
//            const auto& pointB = arr[i + 1];

//            double x = getPt(pointA.x, pointB.x, perc);
//            double y = getPt(pointA.y, pointB.y, perc);
//            double z = getPt(pointA.z, pointB.z, perc);

//            ans.push_back({x, y, z});
//        }
//        return getBezierPoint3d(ans, perc);
//    }

//}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    setWindowTitle("Поверхность Безье");
    init();
}

MainWindow::~MainWindow()
{
    //delete ui;
}

void MainWindow::init()
{
    row = 5;
    column = 3;

    N = binomialMatrix(row - 1);
    M = binomialMatrix(column - 1);
    M.transpose();

    std::cout << "N\n" << N << "\n";
    std::cout << "M\n" << M << "\n";

    Matrix<Point3d> B(row, column);

    for (int i = 0; i < B.getRow(); ++i){
        for (int j = 0; j < B.getColumn(); ++j){
            B[i][j] = Point3d(i, j, rand() % 10);
        }
    }
    std::cout << "B\n" << B << "\n";
}


Point3d MainWindow::getBezierPoint(double u, double w)
{
    U = bezierBasis(u, column - 1);
    W = bezierBasis(w, row - 1);
    W.transpose();

    Point3d bezierPoint{};// = U * N * B * M * W;// надо пофиксить
    return bezierPoint;
}



