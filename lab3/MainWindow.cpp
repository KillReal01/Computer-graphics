#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <iostream>
#include "matrix.h"
#include "convert.h"
#include "array.h"
#include "bezier.h"
#include "figure.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Лабораторная работа №3");

    row = 10;
    column = 10;

    createBasePoints();
    createBaseFigure();

    // точность для фигуры большой не ставить, факториалы умирают
    createBezierFigure(50);

    double length = 300;
    double scale = 50;
    double delta = 200;

//    line_x = new Figure(std::vector<Edge<Point>>{Edge<Point>({delta + length, length, delta + length}, {delta + length * 2, length, delta + length})},
//                        Point(delta + length, length, delta + length), "X", QPen(Qt::black, 2, Qt::SolidLine));
//    line_y = new Figure(std::vector<Edge<Point>>{Edge<Point>({delta + length, length, delta + length}, {delta + length, length * 2, delta + length})},
//                        Point(delta + length, length, delta + length), "Y", QPen(Qt::black, 2, Qt::SolidLine));
//    line_z = new Figure(std::vector<Edge<Point>>{Edge<Point>({delta + length, length, delta + length}, {delta + length, length, delta + length * 2})},
//                        Point(delta + length, length, delta + length), "Z", QPen(Qt::black, 2, Qt::SolidLine));

    figure_base->rotationOY(30);
    figure_base->rotationOX(-30);
    figure_base->rotationOZ(180);
    ui->canvas->DrawItem(figure_base);

    figure_bezier->rotationOY(30);
    figure_bezier->rotationOX(-30);
    figure_bezier->rotationOZ(180);
    ui->canvas->DrawItem(figure_bezier);

    ui->canvas->SetSceneRect(QPoint(0, 0), QPoint(700, 500));

//    for (auto& obj : {line_x, line_y, line_z}) {
//        obj->rotationOY(30);
//        obj->rotationOX(-30);
//        obj->rotationOZ(180);

//        ui->canvas->DrawItem(obj);
//        double x = obj->getData()[0].getEnd().getData()[0];
//        double y = obj->getData()[0].getEnd().getData()[1];
//        ui->canvas->AddText(obj->getName(), QFont("Times", 15), x, y);
//    }

    prev_angle_x_ = prev_angle_y_ = prev_angle_z_ = 0;
    for (auto scroll_bar : {ui->scrollBarOX, ui->scrollBarOY, ui->scrollBarOZ}) {
        scroll_bar->setRange(0, 360);
        scroll_bar->setValue(0);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::createBasePoints(){
    B = Matrix<Point>(row, column);
    for (int i = 0; i < B.getRow(); ++i){
        for (int j = 0; j < B.getColumn(); ++j){
            //B[i][j] = Point(i, j, (rand() % 200) / 100.0);
            B[i][j] = Point(i, j, rand() % 5);
            //B[i][j] = Point(i, j, i + j);
        }
    }
    //std::cout << "B\n" << B << "\n";
}

void MainWindow::createBaseFigure()
{
    std::vector<Edge<Point>> edges_base;

    double scalefig = 50;
    // base points
    // horizontal lines
    for (int i = 0; i < B.getRow(); ++i){
        for (int j = 0; j < B.getColumn() - 1; ++j){
            Point prev = scalefig * B[i][j];
            Point newpoint = scalefig * B[i][j + 1];
            edges_base.push_back(Edge(prev, newpoint));
            prev = newpoint;
        }
    }
    // vertical lines
    for (int i = 0; i < B.getRow() - 1; ++i){
        for (int j = 0; j < B.getColumn(); ++j){
            Point prev = scalefig * B[i][j];
            Point newpoint = scalefig * B[i + 1][j];
            edges_base.push_back(Edge(prev, newpoint));
            prev = newpoint;
        }
    }

    Point center(scalefig * row / 2, scalefig * column / 2, scalefig / 2);
    figure_base = new Figure(edges_base, center, "Base surface", QPen(Qt::blue, 1, Qt::SolidLine));
}


void MainWindow::createBezierFigure(int accuracy)
{
    std::vector<Edge<Point>> edges_bezier;

    Matrix<Point> bezier = createBezierSurface(accuracy, B);

    double scalefig = 50;

    // bezier points
    // horizontal lines
    for (int i = 0; i < bezier.getRow(); ++i){
        for (int j = 0; j < bezier.getColumn() - 1; ++j){
            Point prev = scalefig * bezier[i][j];
            Point newpoint = scalefig * bezier[i][j + 1];
            edges_bezier.push_back(Edge(prev, newpoint));
            prev = newpoint;
        }
    }
    // vertical lines
    for (int i = 0; i < bezier.getRow() - 1; ++i){
        for (int j = 0; j < bezier.getColumn(); ++j){
            Point prev = scalefig * bezier[i][j];
            Point newpoint = scalefig * bezier[i + 1][j];
            edges_bezier.push_back(Edge(prev, newpoint));
            prev = newpoint;
        }
    }

    Point center(scalefig * row / 2, scalefig * column / 2, scalefig / 2);
    figure_bezier = new Figure(edges_bezier, center, "Bezier surface", QPen(Qt::red, 1, Qt::SolidLine));
}



void MainWindow::on_scrollBarOX_valueChanged(int value)
{
    int diff_angle = value - prev_angle_x_;
    prev_angle_x_ = value;
    figure_base->rotationOX(diff_angle);
    figure_bezier->rotationOX(diff_angle);
    ui->canvas->Repaint();
}


void MainWindow::on_scrollBarOY_valueChanged(int value)
{
    int diff_angle = value - prev_angle_y_;
    prev_angle_y_ = value;
    figure_base->rotationOY(diff_angle);
    figure_bezier->rotationOY(diff_angle);
    ui->canvas->Repaint();
}

void MainWindow::on_scrollBarOZ_valueChanged(int value)
{
    int diff_angle = value - prev_angle_z_;
    prev_angle_z_ = value;
    figure_base->rotationOZ(diff_angle);
    figure_bezier->rotationOZ(diff_angle);
    ui->canvas->Repaint();
}


