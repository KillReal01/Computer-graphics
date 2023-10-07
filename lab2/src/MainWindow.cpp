#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDebug>

namespace
{ 
    double getPt(int n1, int n2, double perc)
    {
        double diff = n2 - n1;
        return n1 + ( diff * perc );
    }

    std::vector<std::pair<int, int>> getBezierPoint(const std::vector<std::pair<int, int>>& arr, double perc) {
        if (arr.size() <= 1) {
            return arr;
        }

        std::vector<std::pair<int, int>> ans;
        for (int i = 0; i < arr.size() - 1; i++) {
            const auto& pointA = arr[i];
            const auto& pointB = arr[i + 1];

            double x = getPt(pointA.first, pointB.first, perc);
            double y = getPt(pointA.second, pointB.second, perc);

            ans.push_back({x, y});
        }

        return getBezierPoint(ans, perc);
    }

} // namespace

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Кривая Безье");
    std::vector<std::pair<int, int>> arr_coord {
        {200, 500},
        {500, 200},
        {300, 300},
    };

    for (int i = 0; i < 3; i++) {
        //new name for points
        TVertex* vertex = new TVertex('P' + QString::number(i));
        vertex->setPos(arr_coord[i].first, arr_coord[i].second);
        connect(vertex, &TVertex::move, this, &MainWindow::changeVertex);
        ui->widget->DrawItem(vertex);
        _vertexes.push_back(vertex);
    }
    repaint();
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

    std::vector<std::pair<int, int>> ans;
    for(float i = 0 ; i < 1 ; i += 0.01)
    {
        auto point = getBezierPoint(main_points, i).back();
        double x = point.first;
        double y = point.second;

        ans.push_back({x, y});
    }

    for(int i = 0; i < ans.size() - 1; i++)
        _lines.push_back(new Line(ans[i].first, ans[i].second, ans[i+1].first, ans[i+1].second));

    for(int i = 0; i < main_points.size() - 1; i++)
        _lines.push_back(new Line(main_points[i].first, main_points[i].second, main_points[i+1].first, main_points[i+1].second));

    ui->widget->DrawLines(_lines);
    //ui->widget->DrawLines(main_points);
}

void MainWindow::changeVertex()
{
    repaint();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_buttonAdd_clicked()
{
    //new name for points
    TVertex* vertex = new TVertex('P' + QString::number(_vertexes.size()));
    vertex->setPos(300, 300);
    connect(vertex, &TVertex::move, this, &MainWindow::changeVertex);
    _vertexes.push_back(vertex);
    ui->widget->DrawItem(vertex);
    repaint();
}


void MainWindow::on_buttonRemove_clicked()
{
    if (_vertexes.size() <= 3)
        return;

    delete _vertexes.back();
    _vertexes.pop_back();
    repaint();
}

