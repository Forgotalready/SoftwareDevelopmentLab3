#include "MainWindow.h"

void MainWindow::setupGUI()
{
    QSplitter* splitter= new QSplitter(this);

    treeView = new QTreeView(splitter);

    tableView = new QTableView(splitter);

    splitter->addWidget(treeView);
    splitter->addWidget(chartView);
    setCentralWidget(splitter);

    setGeometry(100, 100, 1500, 500);
    setStatusBar(new QStatusBar(this));
    statusBar()->showMessage("Choosen Path: ");
}

void MainWindow::setupChart()
{
    QChart *chart = new QChart();
    QPieSeries *series = new QPieSeries();

    for (int row = 0; row < fileModel->rowCount(QModelIndex()); ++row) {
        QString label = fileModel->data(fileModel->index(row, 0)).toString();
        double value = fileModel->data(fileModel->index(row, 1)).toDouble();
        series->append(label, value);
    }

    chart->addSeries(series);
    chart->setTitle("Pie Chart Example");
    chart->legend()->show();

    for (QPieSlice *slice : series->slices()) {
        slice->setLabel(QString("%1: %2%").arg(slice->label()).arg(100 * slice->percentage(), 0, 'f', 1));
    }

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupGUI();

    QString homePath = QDir::currentPath();

    directoryModel = new QFileSystemModel(this);
    directoryModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    directoryModel->setRootPath(homePath);
    treeView->setModel(directoryModel);
    treeView->expandAll();

    QItemSelectionModel *selectionModel = treeView->selectionModel();

    QItemSelection toggleSelection;
    QModelIndex topLeft;
    topLeft = directoryModel->index(homePath);
    directoryModel->setRootPath(homePath);

    toggleSelection.select(topLeft, topLeft);
    selectionModel->select(toggleSelection, QItemSelectionModel::Toggle);

    strat = std::make_shared<BySizeTraversal>();
    context.setStrategy(strat);
    QMap<QString, double> data = formOtherGroup(*(context.executeStrategy(QDir::currentPath())));
    fileModel = new FileSystemModel(data, this);
    tableView->setModel(fileModel);

    connect(
       selectionModel,
       &QItemSelectionModel::selectionChanged,
       this,
        &MainWindow::onSelectionChange
    );
    connect(
        this,
        &MainWindow::pathChange,
        fileModel,
        &FileSystemModel::setNewMap
    );

    QModelIndex index = treeView->selectionModel()->currentIndex();
    int length = 200;
    int dx = 30;

    if (directoryModel->fileName(index).length() * dx > length) {
        length = length + directoryModel->fileName(index).length() * dx;
        qDebug() << "r = " << index.row() << "c = " << index.column() << directoryModel->fileName(index) << directoryModel->fileInfo(index).size();
    }
}

void MainWindow::onSelectionChange(const QItemSelection &selected, [[maybe_unused]] const QItemSelection &deselected)
{
    QModelIndex index = treeView->selectionModel()->currentIndex();
    QModelIndexList indexs =  selected.indexes();
    QString filePath = "";

    // Размещаем инфо в statusbar относительно выделенного модельного индекса

    if (indexs.count() >= 1) {
        QModelIndex ix =  indexs.constFirst();
        filePath = directoryModel->filePath(ix);
        this->statusBar()->showMessage("Выбранный путь : " + directoryModel->filePath(indexs.constFirst()));
    }

    int length = 200;
    int dx = 30;

    if (directoryModel->fileName(index).length() * dx > length) {
        length = length + directoryModel->fileName(index).length() * dx;
        qDebug() << "r = " << index.row() << "c = " << index.column() << directoryModel->fileName(index) << directoryModel->fileInfo(index).size();
    }
    treeView->header()->resizeSection(index.column(), length + directoryModel->fileName(index).length());
    QMap<QString, double> newStat = formOtherGroup(*(context.executeStrategy(directoryModel->filePath(indexs.constFirst()))));
    emit pathChange(newStat);
    //tableView->setRootIndex(fileModel->setRootPath(filePath));
}

