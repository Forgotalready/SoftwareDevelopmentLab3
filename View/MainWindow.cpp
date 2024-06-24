#include "MainWindow.h"

void MainWindow::setupGUI()
{
    splitter= new QSplitter(this);

    treeView = new QTreeView(splitter);

    statisticViewAdapter = new TableViewAdapter();

    splitter->addWidget(treeView);

    statisticViewAdapter->updateView(splitter, fileModel);

    setCentralWidget(splitter);

    setGeometry(100, 100, 1500, 500);
    setStatusBar(new QStatusBar(this));
    statusBar()->showMessage("Choosen Path: ");
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    strat = std::make_shared<BySizeTraversal>();
    context.setStrategy(strat);
    QMap<QString, double> data = formOtherGroup(*(context.executeStrategy(QDir::currentPath())));
    fileModel = new FileSystemModel(data, this);

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


    //tableView->setModel(fileModel);

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
    statisticViewAdapter->updateView(splitter, fileModel);
    //tableView->setRootIndex(fileModel->setRootPath(filePath));
}

