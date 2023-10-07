{
    ui->setupUi(this);

    std::vector<std::pair<int, int>> arr_coord {
        {200, 700},
        {500, 200},
        {700, 500},
    };

    for (int i = 0; i < 3; i++) {
        TVertex* vertex = new TVertex(QString::number(i));
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
    TVertex* vertex = new TVertex(QString::number(_vertexes.size()));
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


