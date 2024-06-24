#include "Chart.h"
Chart::Chart() {}

void Chart::drawChart()
{
    chart->legend()->show();
    chartView->setChart(chart);
}

void Chart::drawLegend()
{

}

void PieChart::createChart(FileSystemModel *model)
{
    chart = new QChart();
    series = new QPieSeries();

    for (int row = 0; row < model->rowCount(QModelIndex()); ++row) {
        QString label = model->data(model->index(row, 0)).toString();
        double value = model->data(model->index(row, 1)).toDouble();
        series->append(label, value);
    }
    chart->addSeries(series);
}
