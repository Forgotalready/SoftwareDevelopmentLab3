#ifndef CHART_H
#define CHART_H

#include <QChartView>
#include <QChart>
#include <QAbstractSeries>
#include <QPieSeries>

#include "Model/FileSystemModel.h"

using namespace QtCharts;
class Chart
{
protected:
    QChartView *chartView;
    QChart *chart;

public:
    Chart();

    virtual void createChart(FileSystemModel*) = 0;
    void drawChart();
    void drawLegend();
    QChartView* creatChartView(FileSystemModel* model){
        createChart(model);
        drawChart();
        drawLegend();
        return chartView;
    }
};


class PieChart : public Chart{

    QPieSeries* series;
    // Chart interface
public:
    void createChart(FileSystemModel*) override;
};
#endif // CHART_H
