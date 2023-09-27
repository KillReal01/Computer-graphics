#include "Canvas.h"
#include "ui_Canvas.h"
#include <QDebug>
#include "vertex.h"

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

Canvas::Canvas(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Canvas)
    , _pen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap))
    , _zoom(100)
    , _textItem(nullptr)
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
    int delta_x = 0;
    int delta_y = 0;
    _zoom = 100;
    for (const auto& edge : figure.getPerspective()) {
        // painter.drawLine(0, 0, 400, 400);
        int x1 = qRound(edge.getStartVector().x * _zoom + delta_x);
        int y1 = qRound(edge.getStartVector().y * _zoom + delta_y);
        int x2 = qRound(edge.getEndVector().x * _zoom + delta_x);
        int y2 = qRound(edge.getEndVector().y * _zoom + delta_y);
        auto* line = new Line(x1, y1, x2, y2);

        _scene->addItem(line);
        //qDebug() << edge.getStartVector().x * _zoom << " " << edge.getStartVector().y * _zoom << " " << edge.getEndVector().x * _zoom << " " << edge.getEndVector().y * _zoom;
    }
    //_cur_figure = figure;
    //repaint();
}

void Canvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
}

void Canvas::DrawText(const QString& text)
{
    if (_textItem)
        _textItem->deleteLater();

    _textItem = _scene->addText(text, QFont("Arial", 30));
    _textItem->setPos(QPoint(0, 0));
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
