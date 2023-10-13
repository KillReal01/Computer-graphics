#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include "matrix.h"
#include "convert.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::vector<Edge<Point>> edges {

        Edge<Point>({300, 300, 200}, {300, 200, 200}),
        /*Edge<Point>({200, 300, 200}, {300, 300, 200}),
        Edge<Point>({300, 300, 200}, {300, 300, 300}),

        Edge<Point>({200, 200, 200}, {300, 200, 200}),
        Edge<Point>({200, 200, 200}, {200, 300, 200}),
        Edge<Point>({200, 200, 200}, {200, 200, 300}),

        Edge<Point>({200, 300, 300}, {200, 300, 200}),
        Edge<Point>({200, 300, 300}, {200, 200, 300}),
        Edge<Point>({200, 300, 300}, {300, 300, 300}),

        Edge<Point>({300, 200, 300}, {200, 200, 300}),
        Edge<Point>({300, 200, 300}, {300, 300, 300}),
        Edge<Point>({300, 200, 300}, {300, 200, 200}),*/

    };

    figure_ = new Figure(edges, Point(250, 250, 250));
    ui->canvas->DrawItem(figure_);
    //ui->canvas->DrawFigure(figure_);
    //ui->horizontalScrollBar->setRange(0, 360);
    _prev_angle = 0;
    ui->horizontalScrollBar->setRange(0, 360);
    ui->horizontalScrollBar->setValue(_prev_angle);

    auto point = Point{300, 0, 300};
    auto mtr = Matrix<double>(point.getData());
    auto ans = mtr * rotationMatrixOZ(4);
    qDebug() << ans.getMatrix()[0];
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_horizontalScrollBar_valueChanged(int value)
{
    int diff_angle = value - _prev_angle;
    _prev_angle = value;
    figure_->rotationOY(1);
    ui->canvas->Repaint();
    //qDebug() << diff_angle;
    for (const auto& edge : figure_->getData()) {
        std::cout << edge.getStart() << " | " << edge.getEnd() << std::endl;
    }

}

