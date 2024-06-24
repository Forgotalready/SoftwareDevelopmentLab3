#include "ViewAdapter.h"

#include <QChart>
#include <QPieSeries>
using namespace QtCharts;

ViewAdapter::ViewAdapter() {}

void PieChartAdapter::updateView(QSplitter *&splitter, FileSystemModel* model)
{
    if(chartView != nullptr) {
        delete chartView;
        chartView = nullptr;
    }

    QChart *chart = new QChart();
    QPieSeries *series = new QPieSeries();

    for (int row = 0; row < model->rowCount(QModelIndex()); ++row) {
        QString label = model->data(model->index(row, 0)).toString();
        double value = model->data(model->index(row, 1)).toDouble();
        series->append(label, value);
    }

    chart->addSeries(series);
    chart->setTitle("Pie Chart");
    chart->legend()->show();

    for (QPieSlice *slice : series->slices()) {
        slice->setLabel(QString("%1: %2%").arg(slice->label()).arg(100 * slice->percentage(), 0, 'f', 1));
    }

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);


    QWidget* last = splitter->replaceWidget(1, chartView);
    if(last == nullptr){
        splitter->addWidget(chartView);
        return;
    }
    delete last;
}

void TableViewAdapter::updateView(QSplitter *&splitter, FileSystemModel *model)
{
    if(tableView != nullptr){
        delete tableView;
        tableView = nullptr;
    }
    tableView = new QTableView();
    tableView->setModel(model);

    QWidget* last = splitter->replaceWidget(1, tableView);
    if(last == nullptr){
        splitter->addWidget(tableView);
        return;
    }
    delete last;
}
