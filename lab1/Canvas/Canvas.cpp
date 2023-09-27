#include "Canvas.h"
#include "ui_Canvas.h"
#include <QDebug>

namespace{
    enum DIRECTION {
        x = 1,
        y = 2,
        z = 3
    };
}

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
    _const_figure = figure;
    _cur_figure = _const_figure;
    _cur_figure.rotation(DIRECTION::x, 10);
    repaint();
}

void Canvas::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(_pen);

    int delta_x = 400;
    int delta_y = 250;

    _cur_figure = _const_figure;
    _cur_figure.rotation(DIRECTION::x, 10);

    for (const auto& edge : _cur_figure.getPerspective()) {
        int x1 = qRound(edge.getStartVector().x * _zoom + delta_x);
        int y1 = qRound(edge.getStartVector().y * _zoom + delta_y);
        int x2 = qRound(edge.getEndVector().x * _zoom + delta_x);
        int y2 = qRound(edge.getEndVector().y * _zoom + delta_y);
        painter.drawLine(x1, y1, x2, y2);
    }
}

void Canvas::Rotation(int angle)
{
    _const_figure.rotation(DIRECTION::z, angle);
    repaint();
}
