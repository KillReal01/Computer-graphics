#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(600, 700);

    // Холст
    canvas = new Canvas(this);
    canvas->move((this->width() - canvas->width()) / 2, 10);
    canvas->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete canvas;
}

