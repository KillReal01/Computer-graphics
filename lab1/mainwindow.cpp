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
    std::vector<Edge<Point3d>> edges {
        Edge<Point3d>({0.17, 0.98, 0}, {0, 0, 0}),
        Edge<Point3d>({0.17, 0.98, 0}, {1.15, 0.81, 0}),
        Edge<Point3d>({0.17, 0.98, 0}, {0.17, 0.98, 1}),

        Edge<Point3d>({0.98, -0.17, 0}, {1.15, 0.81, 0}),
        Edge<Point3d>({0.98, -0.17, 0}, {0.98, -0.17, 1}),
        Edge<Point3d>({0.98, -0.17, 0}, {0, 0, 0}),

        Edge<Point3d>({0, 0, 1}, {0.17, 0.98, 1}),
        Edge<Point3d>({0, 0, 1}, {0.98, -0.17, 1}),
        Edge<Point3d>({0, 0, 1}, {0, 0, 0}),

        Edge<Point3d>({1.15, 0.81, 1}, {0.98, -0.17, 1}),
        Edge<Point3d>({1.15, 0.81, 1}, {0.17, 0.98, 1}),
        Edge<Point3d>({1.15, 0.81, 1}, {1.15, 0.81, 0}),
    };
    Figure figure(edges);
    ui->canvas->DrawFigure(figure);
}

MainWindow::~MainWindow()
{
    delete ui;
}
