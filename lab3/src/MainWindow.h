#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "structure.h"
#include "matrix.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int row, column;
    Matrix<double> U, W, N, M;
    Matrix<Point3d> B;

    void init();
    Point3d getBezierPoint(double u, double w);
};

#endif // MAINWINDOW_H
