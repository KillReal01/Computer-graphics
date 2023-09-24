#include "Canvas.h"
#include "ui_Canvas.h"
#include <QDebug>

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

    const int delta_x = 400;
    const int delta_y = 250;

    for (const auto& edge : _cur_figure.getPerspective()) {
        // painter.drawLine(0, 0, 400, 400);
        const int x1 = qRound(edge.getStartVector().x * _zoom + delta_x);
        const int y1 = qRound(edge.getStartVector().y * _zoom + delta_y);
        const int x2 = qRound(edge.getEndVector().x * _zoom + delta_x);
        const int y2 = qRound(edge.getEndVector().y * _zoom + delta_y);

        painter.drawLine(x1, y1, x2, y2);
        //qDebug() << edge.getStartVector().x * _zoom << " " << edge.getStartVector().y * _zoom << " " << edge.getEndVector().x * _zoom << " " << edge.getEndVector().y * _zoom;
    }
}

void Canvas::Rotation(int angle)
{
    _cur_figure.rotation(angle);
    repaint();
}
