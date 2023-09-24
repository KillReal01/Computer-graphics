#include "Canvas.h"
#include "ui_Canvas.h"
#include <QDebug>

const int SCREEN_WIDTH = 800;
const int SCREEN_HIGHT = 600;

Canvas::Canvas(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Canvas)
    , _pen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap))
    , _zoom(100)
{
    ui->setupUi(this);
}

Canvas::~Canvas()
{
    delete ui;
}

void Canvas::DrawFigure(const Figure& figure)
{
    _cur_figure = figure;
    repaint();
}

void Canvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(_pen);
    //painter.drawLine(0, 0, 300, 300);
    //painter.drawLine(300, 300, 600, 800);

    for (int i = 0; i < _lines.size() - 1; i++) {
        const auto& pointA = _lines[i];
        const auto& pointB = _lines[i + 1];
        painter.drawLine(pointA.first, SCREEN_HIGHT - pointA.second, pointB.first, SCREEN_HIGHT - pointB.second);
    }
}

void Canvas::DrawLines(const std::vector<std::pair<int, int>>& arr)
{
    _lines = arr;
    repaint();
}

void Canvas::Rotation(int angle)
{
    _cur_figure.rotation(angle);
    repaint();
}
