#include "MainWindow.h"

void MainWindow::setupGUI()
{
    QSplitter* splitter= new QSplitter(this);

    treeView = new QTreeView(splitter);

    tableView = new QTableView(splitter);

    splitter->addWidget(treeView);
    splitter->addWidget(tableView);
    setCentralWidget(splitter);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupGUI();

    strat = std::make_shared<BySizeTraversal>();
    context.setStrategy(strat);

    QMap<QString, double> data = *(context.executeStrategy(QDir::rootPath()));

    directoryModel = new QFileSystemModel(this);
    directoryModel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    directoryModel->setRootPath(QDir::rootPath());
    treeView->setModel(directoryModel);

    fileModel = new FileSystemModel(data, this);
    tableView->setModel(fileModel);
}

