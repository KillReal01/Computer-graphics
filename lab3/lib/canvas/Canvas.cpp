#include "Canvas.h"
#include "ui_Canvas.h"
#include <QDebug>
#include "vertex.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

Canvas::Canvas(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Canvas)
    , _pen(QPen(Qt::green, 1, Qt::SolidLine, Qt::FlatCap))
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
    for (int i = 0; i < arr.size() - 1; i++) {
        const auto& pointA = arr[i];
        const auto& pointB = arr[i + 1];
        auto* line = new Line(pointA.first, pointA.second, pointB.first, pointB.second);
        _scene->addItem(line);
    }
}

void Canvas::DrawLines(const std::vector<Line*>& arr)
{
    for (int i = 0; i < arr.size(); i++) {
        _scene->addItem(arr[i]);
    }
}


void Canvas::DrawItem(QGraphicsItem* item)
{
    _scene->addItem(item);
}


void Canvas::Rotation(int angle)
{
    _cur_figure.rotation(angle);
    repaint();
}
