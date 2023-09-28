#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("3d модель");
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

    _figure = new Figure(edges);
    //ui->canvas->DrawFigure(*_figure);
    ui->horizontalScrollBar->setRange(0, 360);
    _prev_angle = 0;
    ui->horizontalScrollBar->setValue(_prev_angle);
    repaint("0");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::repaint(const QString& angle)
{
    for (auto& line : _lines)
        delete line;
    _lines.clear();

    int delta_x = 300;
    int delta_y = 250;
    int zoom = 100;

    for (const auto& edge : _figure->getPerspective()) {
        int x1 = qRound(edge.getStartVector().x * zoom + delta_x);
        int y1 = qRound(edge.getStartVector().y * zoom + delta_y);
        int x2 = qRound(edge.getEndVector().x * zoom + delta_x);
        int y2 = qRound(edge.getEndVector().y * zoom + delta_y);
        auto* line = new Line(x1, y1, x2, y2);

        _lines.push_back(line);
    }
    QString str = "Angle = " + angle + "°";
    ui->canvas->DrawText(str);
    ui->canvas->DrawLines(_lines);
}

void MainWindow::on_horizontalScrollBar_valueChanged(int value)
{
    _figure->rotation(DIRECTION::z, value - _prev_angle);
    repaint(QString::number(value));
    _prev_angle = value;
}

