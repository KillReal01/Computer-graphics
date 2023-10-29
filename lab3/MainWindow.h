#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "geometry/figure.h"
#include "geometry/point.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_scrollBarOZ_valueChanged(int value);
    void on_scrollBarOX_valueChanged(int value);
    void on_scrollBarOY_valueChanged(int value);

    void on_buttonCreateRandom_clicked();

private:
    Ui::MainWindow *ui;

    Figure* figure_base, *figure_bezier;
    Point point;
    int prev_angle_x_;
    int prev_angle_y_;
    int prev_angle_z_;

    Figure* line_x;
    Figure* line_y;
    Figure* line_z;
    Figure* axes;

    int row, column;
    Matrix<Point> B;

    void createRandomBezier(int row = 10, int column = 10, int accuracy = 50);
};
#endif // MAINWINDOW_H
