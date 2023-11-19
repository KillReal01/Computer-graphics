#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>
#include <QPen>
#include <algorithm>

#define LEFT  1  /* двоичное 0001 */
#define RIGHT 2  /* двоичное 0010 */
#define BOT   4  /* двоичное 0100 */
#define TOP   8  /* двоичное 1000 */


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Лабораторная работа №4");
    _window = QRectF(0, 0, 0, 0);
    randomSegments(count_lines);
}


void MainWindow::changeRectangle()
{
    QObject* sender = QObject::sender();
    TVertex* vertex = qobject_cast<TVertex*>(sender);

    int _x = vertex->pos().x();
    int _y = vertex->pos().y();

    auto itr = std::find(_vertexes.begin(), _vertexes.end(), vertex);
    int pos = std::distance(_vertexes.begin(), itr);

    TVertex* next = _vertexes[(pos + 1) % _vertexes.size()];
    TVertex* prev = _vertexes[(pos - 1) % _vertexes.size()];

    if (pos % 2 == 0)
    {
        prev->setPos(prev->pos().x(), _y);
        next->setPos(_x, next->pos().y());
    }
    else
    {
        prev->setPos(_x, prev->pos().y());
        next->setPos(next->pos().x(), _y);
    }

    int w = _vertexes[3]->pos().x() -_vertexes[0]->pos().x();
    int h = _vertexes[1]->pos().y() -_vertexes[0]->pos().y();
    _window = QRectF(_vertexes[0]->pos().x(), _vertexes[0]->pos().y(), w, h);

    fillMap();
    repaint();
}

MainWindow::~MainWindow()
{
    for (auto& line : _lines)
        delete line;
    _lines.clear();

    for (auto& line : _segments)
        delete line;
    _segments.clear();

    for (auto& line : _convert_segments)
        delete line;
    _convert_segments.clear();

    for (auto& v : _vertexes){
        disconnect(v, &TVertex::move, this, &MainWindow::changeRectangle);
        delete v;
    }
    delete ui;
}

namespace{
bool comparePoints(const QPointF& p1, const QPointF& p2) {
    if (p1.x() != p2.x())
        return p1.x() < p2.x();
    else
        return p1.y() < p2.y();
}
}

std::vector<Line *> MainWindow::algorithm(const std::vector<Line*>& _segments)
{
    std::vector<Line*> _new;

    QPen penInside(Qt::green, 2, Qt::SolidLine);
    QPen penOutside(Qt::black, 2, Qt::SolidLine);

    for (const auto& segment : _segments){
        QPointF start = segment->getStart();
        QPointF end = segment->getEnd();

        int key_start = 0;
        int key_end = 0;

        foreach (int key, _map.keys()) {
            auto rect = _map.value(key);
            if (isBelong(rect, start))
                key_start = key;
            if (isBelong(rect, end))
                key_end = key;
        }
        if (key_start == 0 && key_end == 0)//full inside
        {
            _new.push_back(new Line(start.x(), start.y(), end.x(), end.y(), penInside));
            continue;
        }
        if ((key_start & key_end) != 0)//full outside
        {
            _new.push_back(new Line(start.x(), start.y(), end.x(), end.y(), penOutside));
            continue;
        }

        std::vector<QPointF> p = intersectionRect(_window, segment);
        p.push_back(start);
        p.push_back(end);
        std::sort(p.begin(), p.end(), comparePoints);

//        qDebug() << "algorithm:";
//        for (auto & iter : p){
//            qDebug() << iter;
//        }

//        qDebug() << "algorithm:" << p.size();

        if (p.size() > 2){
            if (isBelong(_window, p[0]))
            {
                _new.push_back(new Line(p[p.size() - 1].x(), p[p.size() - 1].y(), p[p.size() - 2].x(), p[p.size() - 2].y(), penOutside));
                _new.push_back(new Line(p[p.size() - 2].x(), p[p.size() - 2].y(), p[p.size() - 3].x(), p[p.size() - 3].y(), penInside));
            }
            else if (isBelong(_window, p[p.size() - 1]))
            {
                _new.push_back(new Line(p[0].x(), p[0].y(), p[1].x(), p[1].y(), penOutside));
                _new.push_back(new Line(p[1].x(), p[1].y(), p[2].x(), p[2].y(), penInside));
            }
            else if (p.size() == 4)
            {
                _new.push_back(new Line(p[0].x(), p[0].y(), p[1].x(), p[1].y(), penOutside));
                _new.push_back(new Line(p[1].x(), p[1].y(), p[2].x(), p[2].y(), penInside));
                _new.push_back(new Line(p[2].x(), p[2].y(), p[3].x(), p[3].y(), penOutside));
            }
        }
    }

    return _new;
}

void MainWindow::repaint()
{
    for (auto& line : _lines)
        delete line;
    _lines.clear();

    std::vector<std::pair<int, int>> main_points;
    for (int i = 0; i < _vertexes.size(); i++) {
        main_points.push_back({_vertexes[i]->x(), _vertexes[i]->y()});
    }

    QPen pen(Qt::red, 2, Qt::SolidLine);
    int size = main_points.size();
    for(int i = 0; i < size; i++)
    {
        _lines.push_back(new Line(main_points[i % size].first, main_points[i % size].second, main_points[(i+1) % size].first, main_points[(i+1) % size].second, pen));
    }
    ui->widget->DrawLines(_lines);


    for (auto& line : _convert_segments)
        delete line;
    _convert_segments.clear();

    if (_window != QRectF(0,0,0,0)){
        _convert_segments = algorithm(_segments);
        ui->widget->DrawLines(_convert_segments);
    }
}


std::vector<QPointF> MainWindow::intersectionRect(const QRectF& rect, const Line* line)
{
    std::vector<QPointF> res;
    QPointF a = rect.topLeft();
    QPointF b = rect.bottomLeft();
    QPointF c = rect.bottomRight();
    QPointF d = rect.topRight();

    std::vector<Line*> _edges;
    _edges.push_back(new Line(a.x(), a.y(), b.x(), b.y()));
    _edges.push_back(new Line(b.x(), b.y(), c.x(), c.y()));
    _edges.push_back(new Line(c.x(), c.y(), d.x(), d.y()));
    _edges.push_back(new Line(d.x(), d.y(), a.x(), a.y()));



    QPointF point;
    for (const auto& edge : _edges)
    {
        //qDebug() << "intersectionRect:" << edge->getStart() << edge->getEnd() << line->getStart() << line->getEnd();
        if (intersectionSegments(&point, edge, line)){
            qDebug() << "intersectionRect: true" << point << edge->getStart() << edge->getEnd();
            res.push_back(point);
        }
    }
    qDebug() << "";
    return res;
}


bool MainWindow::pointBelongsToSegments(QPointF point, QPointF segmentStart, QPointF segmentEnd) {
    double minX = std::min(segmentStart.x(), segmentEnd.x());
    double maxX = std::max(segmentStart.x(), segmentEnd.x());
    double minY = std::min(segmentStart.y(), segmentEnd.y());
    double maxY = std::max(segmentStart.y(), segmentEnd.y());

    if (point.x() >= minX && point.x() <= maxX && point.y() >= minY && point.y() <= maxY) {
        return true;
    } else {
        return false;
    }
}

bool MainWindow::intersectionSegments(QPointF *point, const Line * a, const Line * b)
{
    double x1 = a->getStart().x();
    double y1 = a->getStart().y();
    double x2 = a->getEnd().x();
    double y2 = a->getEnd().y();

    double x3 = b->getStart().x();
    double y3 = b->getStart().y();
    double x4 = b->getEnd().x();
    double y4 = b->getEnd().y();

    double determinant = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

    if (determinant != 0) {
        double x = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / determinant;
        double y = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / determinant;

        *point = QPointF(x, y);
        if (pointBelongsToSegments(*point, a->getStart(), a->getEnd()) && pointBelongsToSegments(*point, b->getStart(), b->getEnd())){
            return true;
        }
    }
    return false;
}

bool MainWindow::intersection(QPointF* point, const Line* a, const Line* b)
{
    double k1 = 0, b1 = 0, k2 = 0, b2 = 0;
    equationLine(&k1, &b1, a->getStart(), a->getEnd());
    equationLine(&k2, &b2, b->getStart(), b->getEnd());

    if (k1 == k2)
        return false;

    double x;
    double y;

    if (k1 == std::numeric_limits<double>::infinity())
    {
        x = a->getStart().x();
        y = k2 * x + b2;
    }
    else if (k2 == std::numeric_limits<double>::infinity())
    {
        x = b->getStart().x();
        y = k1 * x + b1;
    }
    else
    {
        x = (b2 - b1) / (k1 - k2);
        y = k1 * x + b1;
    }

    point->setX(x);
    point->setY(y);
    //qDebug() << "intersection" << *point;
    return true;
}

void MainWindow::equationLine(double *k, double *b, const QPointF &start, const QPointF &end)
{
    if (end.x() == start.x()){
        *k = std::numeric_limits<double>::infinity();
    }
    else{
        *k = double(end.y() - start.y()) / double(end.x() - start.x());
        *b = start.y() - (*k) * start.x();
    }
}


void MainWindow::fillMap()
{
    int dx_left = _window.topLeft().x();
    int dx_right = this->width() - _window.topRight().x();

    int dy_top = _window.topLeft().y();
    int dy_bot = this->height() - _window.bottomRight().y();

    int x_window = _window.topRight().x() - _window.topLeft().x();
    int y_window = _window.bottomLeft().y() - _window.topLeft().y();

    _map[TOP + LEFT] = QRectF(0, 0, dx_left, dy_top);
    _map[TOP] = QRectF(dx_left, 0, x_window, dy_top);
    _map[TOP + RIGHT] = QRectF(dx_left + x_window, 0, dx_right, dy_top);

    _map[LEFT] = QRectF(0, dy_top, dx_left, y_window);
    _map[0] = _window;
    _map[RIGHT] = QRectF(dx_left + x_window, dy_top, dx_right, y_window);

    _map[BOT + LEFT] = QRectF(0, dy_top + y_window, dx_left, dy_bot);
    _map[BOT] = QRectF(dx_left, dy_top + y_window, x_window, dy_bot);
    _map[BOT + RIGHT] = QRectF(dx_left + x_window, dy_top + y_window, dx_right, dy_bot);

//    foreach (int key, _map.keys()) {
//        auto value = _map.value(key);
//        qDebug() << "Ключ: " << key << ", Значение: " << value;
//    }

}

void MainWindow::randomSegments(int n)
{
    int width = this->width();
    int height = this->height();
    qDebug() << width << height;
    QPen pen(Qt::black, 2, Qt::SolidLine);
    for (int i = 0; i < n; ++i){
        _segments.push_back(new Line(rand() % width, rand() % height, rand() % width, rand() % height, pen));
    }
    ui->widget->DrawLines(_segments);
}

bool MainWindow::isBelong(const QRectF &rect, const QPointF &point)
{
    if (point.x() >= rect.left() && point.x() <= rect.right() && point.y() >= rect.top() && point.y() <= rect.bottom())
        return true;
    else
        return false;
}

void MainWindow::on_pushButtonRandomSegments_clicked()
{
    for (auto& line : _segments)
        delete line;
    _segments.clear();
    randomSegments(count_lines);
    repaint();
}


void MainWindow::on_pushButtonAddWindow_clicked()
{
    for (auto& line : _vertexes)
        delete line;
    _vertexes.clear();

    _window = QRectF(200, 200, 250, 250);
    std::vector<QPointF> arr_coord {
        _window.topLeft(),
        _window.bottomLeft(),
        _window.bottomRight(),
        _window.topRight(),
    };

    for (int i = 0; i < arr_coord.size(); i++) {
        TVertex* vertex = new TVertex("P" + QString::number(i + 1));
        vertex->setPos(arr_coord[i].x(), arr_coord[i].y());
        connect(vertex, &TVertex::move, this, &MainWindow::changeRectangle);
        _vertexes.push_back(vertex);
        ui->widget->DrawItem(vertex);
    }
    fillMap();
    repaint();
}


void MainWindow::on_pushButtonRemoveWindow_clicked()
{
    for (auto& v : _vertexes){
        disconnect(v, &TVertex::move, this, &MainWindow::changeRectangle);
        delete v;
    }
    _vertexes.clear();
    _window = QRectF(0, 0, 0, 0);
    repaint();
}

