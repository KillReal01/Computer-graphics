#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include "matrix.h"
#include "bezier.h"
#include "figure.h"
#include "convert.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    setWindowTitle("Поверхность Безье");
    //init();
    //getBezierPoint(0.5, 0.5);

    std::vector<Edge<Point>> edges {

        Edge<Point>({1, 1, -1}, {1, -1, -1}),
        Edge<Point>({-1, 1, -1}, {1, 1, -1}),
        Edge<Point>({1, 1, -1}, {1, 1, 1}),

        Edge<Point>({-1, -1, -1}, {1, -1, -1}),
        Edge<Point>({-1, -1, -1}, {-1, 1, -1}),
        Edge<Point>({-1, -1, -1}, {-1, -1, 1}),

        Edge<Point>({-1, 1, 1}, {-1, 1, -1}),
        Edge<Point>({-1, 1, 1}, {-1, -1, 1}),
        Edge<Point>({-1, 1, 1}, {1, 1, 1}),

        Edge<Point>({1, -1, 1}, {-1, -1, 1}),
        Edge<Point>({1, -1, 1}, {1, 1, 1}),
        Edge<Point>({1, -1, 1}, {1, -1, -1}),

    };

    Figure figure(edges);
    figure.convertFigure(rotationMatrixOX(20));
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

    B = Matrix<Point>(row, column);

    for (int i = 0; i < B.getRow(); ++i){
        for (int j = 0; j < B.getColumn(); ++j){
            B[i][j] = Point(i, j, rand() % 10);
        }
    }
    std::cout << "B\n" << B << "\n";
}


Point MainWindow::getBezierPoint(double u, double w)
{
    U = bezierBasis(u, column - 1);
    W = bezierBasis(w, row - 1);
    W.transpose();

    Point bezierPoint{};
    // = U * N * B * M * W;// надо пофиксить
//    U * N * B;
//    auto A = B * M * W;
//    std::cout << "Mul\n" << A << "\n";
    return bezierPoint;
}



