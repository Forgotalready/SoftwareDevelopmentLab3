#ifndef VIEWADAPTER_H
#define VIEWADAPTER_H

#include <QSplitter>
#include<QChartView>
#include <QTableView>

#include "Model/FileSystemModel.h"

class ViewAdapter
{
public:
    ViewAdapter();
    virtual void updateView(QSplitter*& splitter, FileSystemModel *model) = 0;
};

class PieChartAdapter : public ViewAdapter
{
private:
    QtCharts::QChartView* chartView;

    // ViewAdapter interface
public:
    void updateView(QSplitter*& splitter, FileSystemModel *model) override;
};

class TableViewAdapter : public ViewAdapter{

    QTableView* tableView;
    // ViewAdapter interface
public:
    void updateView(QSplitter *&splitter, FileSystemModel *model) override;
};
#endif // VIEWADAPTER_H
