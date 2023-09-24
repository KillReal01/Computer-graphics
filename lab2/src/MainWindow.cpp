#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include <QDebug>


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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*{
        const int x1 = 000, y1 = 000;
        const int x2 = 600, y2 = 000;
        const int x3 = 600, y3 = 600;
        const int x4 = 800, y4 = 100;
        const int x5 = 1000, y5 = 300;
        std::vector<std::pair<int, int>> arr {{x1, y1}, {x2, y2}, {x3, y3}, {x4, y4}, {x5, y5}};
        std::vector<std::pair<int, int>> ans;
        for( float i = 0 ; i < 1 ; i += 0.01 )
        {
            auto point = getBezierPoint(arr, i).back();
            double x = point.first;
            double y = point.second;

            ans.push_back({x, y});
            qDebug() << "(" << x << ", " << y << ")";
        }
        ui->widget->DrawLines(ans);
    }*/


    const int x1 = 200, y1 = 700;
    const int x2 = 400, y2 = 200;
    const int x3 = 600, y3 = 100;
    const int x4 = 800, y4 = 500;

    std::vector<std::pair<int, int>> arr_coord {
        {200, 700},
        {400, 200},
        {600, 100},
        {800, 500},
    };

    for (int i = 0; i < 4; i++) {
        TVertex* vertex_1 = new TVertex(QString::number(i));
        vertex_1->setPos(arr_coord[i].first, arr_coord[i].second);
        connect(vertex_1, &TVertex::move, this, &MainWindow::changeVertex);
        arr.push_back(vertex_1);
    }

    std::vector<std::pair<int, int>> arr2 {
        {arr[0]->x(), arr[0]->y()},
        {arr[1]->x(), arr[1]->y()},
        {arr[2]->x(), arr[2]->y()},
        {arr[3]->x(), arr[3]->y()},
    };
    std::vector<std::pair<int, int>> ans;
    for(float i = 0 ; i < 1 ; i += 0.01)
    {
        auto point = getBezierPoint(arr2, i).back();
        double x = point.first;
        double y = point.second;

        ans.push_back({x, y});
        qDebug() << "(" << x << ", " << y << ")";
    }
    ui->widget->DrawLines(ans);
    ui->widget->DrawLines(arr2);
    ui->widget->DrawItem(arr[0]);
    ui->widget->DrawItem(arr[1]);
    ui->widget->DrawItem(arr[2]);
    ui->widget->DrawItem(arr[3]);

}

void MainWindow::changeVertex()
{
    ui->widget->Clear();
    std::vector<std::pair<int, int>> arr2 {
        {arr[0]->x(), arr[0]->y()},
        {arr[1]->x(), arr[1]->y()},
        {arr[2]->x(), arr[2]->y()},
        {arr[3]->x(), arr[3]->y()},
    };
    std::vector<std::pair<int, int>> ans;
    for(float i = 0 ; i < 1 ; i += 0.01)
    {
        auto point = getBezierPoint(arr2, i).back();
        double x = point.first;
        double y = point.second;

        ans.push_back({x, y});
        qDebug() << "(" << x << ", " << y << ")";
    }
    ui->widget->DrawLines(ans);
    ui->widget->DrawLines(arr2);
    //ui->widget->DrawItem(arr[0]);
    //ui->widget->DrawItem(arr[1]);
    //ui->widget->DrawItem(arr[2]);
    //ui->widget->DrawItem(arr[3]);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
    const double x1 = 000, y1 = 000;
    const double x2 = 600, y2 = 000;
    const double x3 = 600, y3 = 600;
    const double x4 = 800, y4 = 200;
    std::vector<std::pair<int, int>> ans;
    for( float i = 0 ; i < 1 ; i += 0.01 )
    {
        // The Green Line
        const double xa = getPt( x1 , x2 , i );
        const double ya = getPt( y1 , y2 , i );
        const double xb = getPt( x2 , x3 , i );
        const double yb = getPt( y2 , y3 , i );

        // The Black Dot
        const double x = getPt( xa , xb , i );
        const double y = getPt( ya , yb , i );

        ans.push_back({x, y});
        qDebug() << "(" << x << ", " << y << ")";
    }



    const double x1 = 000, y1 = 000;
    const double x2 = 600, y2 = 000;
    const double x3 = 600, y3 = 600;
    const double x4 = 800, y4 = 200;
    std::vector<std::pair<int, int>> arr {{x1, y1}, {x2, y2}, {x3, y3}, {x4, y4}};
    std::vector<std::pair<int, int>> ans;
    for( float i = 0 ; i < 1 ; i += 0.01 )
    {
        // The Green Line
        const double _x1 = getPt( x1 , x2 , i );
        const double _y1 = getPt( y1 , y2 , i );
        const double _x2 = getPt( x2 , x3 , i );
        const double _y2 = getPt( y2 , y3 , i );
        const double _x3 = getPt( x3 , x4 , i );
        const double _y3 = getPt( y3 , y4 , i );

        const double __x1 = getPt( _x1 , _x2 , i );
        const double __y1 = getPt( _y1 , _y2 , i );
        const double __x2 = getPt( _x2 , _x3 , i );
        const double __y2 = getPt( _y2 , _y3 , i );

        // The Black Dot
        const double x = getPt( __x1, __x2, i );
        const double y = getPt( __y1, __y2 , i );

        ans.push_back({x, y});
        qDebug() << "(" << x << ", " << y << ")";
    }
*/
