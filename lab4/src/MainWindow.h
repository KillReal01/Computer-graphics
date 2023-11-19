#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vertex.h"
#include "Line.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::vector<TVertex*> _vertexes;
    std::vector<Line*> _segments;
    std::vector<Line*> _convert_segments;
    std::vector<Line*> _lines;
    QMap<int, QRectF> _map;
    QRectF _window;

    std::vector<Line*> algorithm(const std::vector<Line*>&);
    std::vector<QPointF> intersectionRect(const QRectF&, const Line*);
    bool intersectionSegments(QPointF* point, const Line*, const Line*);
    bool pointBelongsToSegments(QPointF point, QPointF segmentStart, QPointF segmentEnd);
    bool intersection(QPointF* point, const Line*, const Line*);
    void equationLine(double* k, double* b, const QPointF& start, const QPointF& end);
    void fillMap();
    void randomSegments(int n);
    bool isBelong(const QRectF&, const QPointF&);
    void repaint();

    int count_lines = 10;

public slots:
    void changeRectangle();

private slots:
    void on_pushButtonRandomSegments_clicked();
    void on_pushButtonAddWindow_clicked();
    void on_pushButtonRemoveWindow_clicked();
};
#endif // MAINWINDOW_H
