#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //{0.17, 0.98, 0}, {0, 0, 0}, {0.98, -0.17, 0}, {1.15, 0.81, 0},
    //{0.17, 0.98, 1}, {0, 0, 1}, {0.98, -0.17, 1}, {1.15, 0.81, 1}

    //пирамида
    std::vector<Edge<Point3d>> edges {

        Edge<Point3d>({1, 1, 1}, {1, -1, 1}),
        Edge<Point3d>({-1, 1, 1}, {1, 1, 1}),
        Edge<Point3d>({1, 1, 1}, {0, 0, -1}),

        Edge<Point3d>({-1, -1, 1}, {1, -1, 1}),
        Edge<Point3d>({-1, -1, 1}, {-1, 1, 1}),
        Edge<Point3d>({-1, -1, 1}, {0, 0, -1}),

        Edge<Point3d>({-1, 1, 1}, {0, 0, -1}),
        Edge<Point3d>({1, -1, 1}, {0, 0, -1}),

    };


    //квадрат
//    std::vector<Edge<Point3d>> edges {

//        Edge<Point3d>({1, 1, -1}, {1, -1, -1}),
//        Edge<Point3d>({-1, 1, -1}, {1, 1, -1}),
//        Edge<Point3d>({1, 1, -1}, {1, 1, 1}),

//        Edge<Point3d>({-1, -1, -1}, {1, -1, -1}),
//        Edge<Point3d>({-1, -1, -1}, {-1, 1, -1}),
//        Edge<Point3d>({-1, -1, -1}, {-1, -1, 1}),

//        Edge<Point3d>({-1, 1, 1}, {-1, 1, -1}),
//        Edge<Point3d>({-1, 1, 1}, {-1, -1, 1}),
//        Edge<Point3d>({-1, 1, 1}, {1, 1, 1}),

//        Edge<Point3d>({1, -1, 1}, {-1, -1, 1}),
//        Edge<Point3d>({1, -1, 1}, {1, 1, 1}),
//        Edge<Point3d>({1, -1, 1}, {1, -1, -1}),

//    };

    Figure figure(edges);
    ui->canvas->DrawFigure(figure);
    ui->horizontalScrollBar->setRange(0, 360);
    _prev_angle = 0;
    ui->horizontalScrollBar->setValue(_prev_angle);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalScrollBar_valueChanged(int value)
{
    ui->canvas->Rotation(value - _prev_angle);
    _prev_angle = value;
}

