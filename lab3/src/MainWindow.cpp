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
    auto N = binomialMatrix(4);
    auto M = binomialMatrix(2);
    M.transpose();
    auto U = bezierBasis(0.5, 4);
    auto W = bezierBasis(0.5, 2);
    W.transpose();

    std::cout << "U\n" <<  U << "\n";
    std::cout << "N\n" << N << "\n";
    std::cout << "M\n" << M << "\n";
    std::cout << "W\n" << W << "\n";

    Matrix<Point3d> B(5, 3);

    for (int i = 0; i < B.getRow(); ++i){
        for (int j = 0; j < B.getColumn(); ++j){
            B[i][j] = Point3d(rand() % 10, rand() % 10, rand() % 10);
        }
    }
    std::cout << "B\n" << B << "\n";

    std::cout << "Multiply\n";
    std::cout << U * N << "\n";
    std::cout << M * W << "\n";

    //N * B; надо пофиксить
}



