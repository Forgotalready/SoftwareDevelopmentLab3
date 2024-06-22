#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QTableView>
#include <QSplitter>
#include <QFileSystemModel>
#include <QStatusBar>
#include <QDebug>
#include <QHeaderView>

#include "Model/FileSystemModel.h"
#include "Domain/Context.h"
#include "Domain/DirectoryTraversal/BySizeTraversal.h"
#include "Domain/DirectoryTraversal/ByTypeTraversal.h"
#include "Domain/DirectoryTraversal/TraversalStrategy.h"

class MainWindow final : public QMainWindow
{
    Q_OBJECT
private:
    QTreeView *treeView;
    QTableView *tableView;
    void setupGUI();
    QFileSystemModel *directoryModel;
    FileSystemModel *fileModel;

    Context context;
    std::shared_ptr<TraversalStrategy> strat;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private slots:
    void onSelectionChange(const QItemSelection &selected, const QItemSelection &deselected);
signals:
    void pathChange(QMap<QString, double>&);
};
#endif // MAINWINDOW_H