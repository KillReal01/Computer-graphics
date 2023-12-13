#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include "matrix.h"
#include "convert.h"
#include "array.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Лабораторная работа №6");

    double side = 200;
    double delta = 200;
    const std::vector<Edge<Point>> edges_figure {
        Edge<Point>({delta + side, delta + side, delta}, {delta + side, delta, delta}),
        Edge<Point>({delta, delta + side, delta}, {delta + side, delta + side, delta}),
        Edge<Point>({delta + side, delta + side, delta}, {delta + side, delta + side, delta + side}),

        Edge<Point>({delta, delta, delta}, {delta + side, delta, delta}),
        Edge<Point>({delta, delta, delta}, {delta, delta + side, delta}),
        Edge<Point>({delta, delta, delta}, {delta, delta, delta + side}),

        Edge<Point>({delta, delta + side, delta + side}, {delta, delta + side, delta}),
        Edge<Point>({delta, delta + side, delta + side}, {delta, delta, delta + side}),
        Edge<Point>({delta, delta + side, delta + side}, {delta + side, delta + side, delta + side}),

        Edge<Point>({delta + side, delta, delta + side}, {delta, delta, delta + side}),
        Edge<Point>({delta + side, delta, delta + side}, {delta + side, delta + side, delta + side}),
        Edge<Point>({delta + side, delta, delta + side}, {delta + side, delta, delta}),
    };

    figure_ = new Figure(edges_figure, Point(delta + side / 2, delta + side / 2, delta + side / 2), "Cube", QPen(Qt::blue, 2, Qt::SolidLine));

    double length = 300;
    delta = 50;

    line_x = new Figure(std::vector<Edge<Point>>{Edge<Point>({delta + length, length, delta + length}, {delta + length * 2, length, delta + length})},
                        Point(delta + length, length, delta + length), "X", QPen(Qt::black, 2, Qt::SolidLine));
    line_y = new Figure(std::vector<Edge<Point>>{Edge<Point>({delta + length, length, delta + length}, {delta + length, length * 2, delta + length})},
                        Point(delta + length, length, delta + length), "Y", QPen(Qt::black, 2, Qt::SolidLine));
    line_z = new Figure(std::vector<Edge<Point>>{Edge<Point>({delta + length, length, delta + length}, {delta + length, length, delta + length * 2})},
                        Point(delta + length, length, delta + length), "Z", QPen(Qt::black, 2, Qt::SolidLine));

    figure_->rotationOY(30);
    figure_->rotationOX(-30);
    figure_->rotationOZ(180);
    ui->canvas->DrawItem(figure_);

    for (auto& obj : {line_x, line_y, line_z}) {
        obj->rotationOY(30);
        obj->rotationOX(-30);
        obj->rotationOZ(180);

        ui->canvas->DrawItem(obj);
        double x = obj->getData()[0].getEnd().getData()[0];
        double y = obj->getData()[0].getEnd().getData()[1];
        ui->canvas->AddText(obj->getName(), QFont("Times", 15), x, y);
    }

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

void MainWindow::on_scrollBarOX_valueChanged(int value)
{
    int diff_angle = value - prev_angle_x_;
    prev_angle_x_ = value;
    figure_->rotationOX(diff_angle);
    ui->canvas->Repaint();
}

void MainWindow::on_scrollBarOY_valueChanged(int value)
{
    int diff_angle = value - prev_angle_y_;
    prev_angle_y_ = value;
    figure_->rotationOY(diff_angle);
    ui->canvas->Repaint();
}

void MainWindow::on_scrollBarOZ_valueChanged(int value)
{
    int diff_angle = value - prev_angle_z_;
    prev_angle_z_ = value;
    figure_->rotationOZ(diff_angle);
    ui->canvas->Repaint();
}


