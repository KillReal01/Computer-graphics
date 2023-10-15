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

private:
    Ui::MainWindow *ui;

    Figure* figure_;
    Point point;
    int prev_angle_x_;
    int prev_angle_y_;
    int prev_angle_z_;

    Figure* line_x;
    Figure* line_y;
    Figure* line_z;
    Figure* axes;
};
#endif // MAINWINDOW_H
