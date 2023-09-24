#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vertex.h"
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
    Ui::MainWindow *ui;
    std::vector<TVertex*> _vertexes;
    void repaint();
    std::vector<Line*> _lines;

public slots:
    void changeVertex();

private slots:
    void on_buttonAdd_clicked();
    void on_buttonRemove_clicked();
};
#endif // MAINWINDOW_H
