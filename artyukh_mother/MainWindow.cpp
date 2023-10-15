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
    this->setWindowTitle("Лабораторная работа №1");

    const std::vector<Edge<Point>> edges_figure {
        Edge<Point>({250, 250, 150}, {250, 150, 150}),
        Edge<Point>({150, 250, 150}, {250, 250, 150}),
        Edge<Point>({250, 250, 150}, {250, 250, 250}),

        Edge<Point>({150, 150, 150}, {250, 150, 150}),
        Edge<Point>({150, 150, 150}, {150, 250, 150}),
        Edge<Point>({150, 150, 150}, {150, 150, 250}),

        Edge<Point>({150, 250, 250}, {150, 250, 150}),
        Edge<Point>({150, 250, 250}, {150, 150, 250}),
        Edge<Point>({150, 250, 250}, {250, 250, 250}),

        Edge<Point>({250, 150, 250}, {150, 150, 250}),
        Edge<Point>({250, 150, 250}, {250, 250, 250}),
        Edge<Point>({250, 150, 250}, {250, 150, 150}),
    };

    figure_ = new Figure(edges_figure, Point(200, 200, 200));
    line_x = new Figure(std::vector<Edge<Point>>{Edge<Point>({300, 300, 300}, {600, 300, 300})}, Point(300, 300, 300));
    line_y = new Figure(std::vector<Edge<Point>>{Edge<Point>({300, 300, 300}, {300, 600, 300})}, Point(300, 300, 300));
    line_z = new Figure(std::vector<Edge<Point>>{Edge<Point>({300, 300, 300}, {300, 300, 600})}, Point(300, 300, 300));

    for (auto& obj : {line_x, line_y, line_z, figure_}) {
        obj->rotationOY(30);
        obj->rotationOX(-30);
        obj->rotationOZ(180);

        ui->canvas->DrawItem(obj);
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


