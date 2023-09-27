#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "figure.h"
#include "Line.h"

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
    void repaint(const QString& angle);

private slots:
    void on_horizontalScrollBar_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    int _prev_angle;
    Figure* _figure;
     std::vector<Line*> _lines;
    //Canvas* canvas;
};
#endif // MAINWINDOW_H
