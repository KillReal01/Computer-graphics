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
    void on_horizontalScrollBar_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    Figure* figure_;
    int _prev_angle;
};
#endif // MAINWINDOW_H
