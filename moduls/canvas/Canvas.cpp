#include "Canvas.h"
#include "ui_Canvas.h"
#include <QDebug>
#include "vertex.h"

const std::int64_t Canvas::SCREEN_WIDTH = 700;
const std::int64_t Canvas::SCREEN_HEIGHT = 500;

Canvas::Canvas(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Canvas)
    , _pen(QPen(Qt::green, 1, Qt::SolidLine, Qt::FlatCap))
    , left_bottom_(0, 0)
    , right_top_(SCREEN_WIDTH, SCREEN_HEIGHT)
{
    ui->setupUi(this);

    _scene = new QGraphicsScene(this);
    UpdateSceneRect();

    ui->graphicsView->setScene(_scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

Canvas::~Canvas()
{
    delete ui;
    delete _scene;
}

void Canvas::UpdateSceneRect()
{
    _scene->setSceneRect(left_bottom_.x(), left_bottom_.y(), right_top_.x(), right_top_.y());
}

void Canvas::SetSceneRect(const QPoint& left_bottom, const QPoint& right_top)
{
    SetSceneRectLeftBottom(left_bottom);
    SetSceneRectRightUp(right_top);
    UpdateSceneRect();
}

void Canvas::SetSceneRectLeftBottom(const QPoint& left_bottom)
{
    left_bottom_ = left_bottom;
    UpdateSceneRect();
}

void Canvas::SetSceneRectRightUp(const QPoint& right_top)
{
    right_top_ = right_top;
    UpdateSceneRect();
}

const QPoint& Canvas::GetSceneRectLeftBottom() const
{
    return left_bottom_;
}

const QPoint& Canvas::GetSceneRectRightUp() const
{
    return right_top_;
}

QGraphicsTextItem* Canvas::AddText(const QString &str, const QFont& font, int x, int y)
{
    QGraphicsTextItem* text = _scene->addText(str, font);
    text->setPos(x, y);
    return text;
}

void Canvas::Repaint()
{
    _scene->update();
}

void Canvas::DrawItem(QGraphicsItem* item)
{
    _scene->addItem(item);
}
