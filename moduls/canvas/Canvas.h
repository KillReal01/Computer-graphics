#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include "figure.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "Line.h"

namespace Ui {
class Canvas;
}

class Canvas : public QWidget
{
    Q_OBJECT

private:
    const static std::int64_t SCREEN_WIDTH;
    const static std::int64_t SCREEN_HEIGHT;

public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas();
    void AddText(const QString& str, const QFont& font, int x, int y);
    void DrawLines(const std::vector<std::pair<int, int>>& arr);
    void DrawLines(const std::vector<Line*>& arr);
    void setPen(const QPen& pen) { _pen = pen; }
    void Rotation(int angle);
    void DrawItem(QGraphicsItem* item);
    void Repaint();

    void SetSceneRect(const QPoint& left_bottom, const QPoint& right_top);
    void SetSceneRectLeftBottom(const QPoint& left_bottom);
    void SetSceneRectRightUp(const QPoint& right_top);

    const QPoint& GetSceneRectLeftBottom() const;
    const QPoint& GetSceneRectRightUp() const;

protected:
    void paintEvent(QPaintEvent *event);
    void UpdateSceneRect();

private:
    Ui::Canvas *ui;
    Figure _cur_figure;
    QPen _pen;

    QGraphicsScene* _scene;

    QPoint left_bottom_;
    QPoint right_top_;
    QPoint center_;
};

#endif // CANVAS_H
