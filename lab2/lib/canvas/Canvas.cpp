#include "Canvas.h"
#include "ui_Canvas.h"
#include <QDebug>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 1000;

Canvas::Canvas(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Canvas)
    , _pen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap))
    , _zoom(100)
{
    ui->setupUi(this);

    _scene = new QGraphicsScene(this);
    _scene->setSceneRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    ui->graphicsView->setScene(_scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

Canvas::~Canvas()
{
    delete ui;
    delete _scene;
}

void Canvas::DrawFigure(const Figure& figure)
{
    _cur_figure = figure;
    repaint();
}

void Canvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
}

void Canvas::DrawLines(const std::vector<std::pair<int, int>>& arr)
{
    _scene->clear();
    for (int i = 0; i < arr.size() - 1; i++) {
        const auto& pointA = arr[i];
        const auto& pointB = arr[i + 1];
        qDebug() << pointA.first << pointA.second<< pointB.first<< pointB.second;
        _scene->addLine(QLine(pointA.first, SCREEN_HEIGHT - pointA.second, pointB.first, SCREEN_HEIGHT - pointB.second));
    }
}

void Canvas::Rotation(int angle)
{
    _cur_figure.rotation(angle);
    repaint();
}
