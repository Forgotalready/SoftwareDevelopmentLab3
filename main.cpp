#include <QDir>
#include <iostream>
#include <QCoreApplication>
#include <vector>
#include <unordered_map>
#include "Domain./DirectoryTraversal/BySizeTraversal.h"
#include <memory>
#include <QTextStream>
typedef std::unordered_map<std::string, long long> Statistic;

void directoryTraversalBySize(QDir directory, Statistic& statistic){
    std::string path = directory.absolutePath().toStdString();
    std::cout << path << std::endl;

    std::cout << "----------\n";

    statistic[path] = 0;

    std::vector<QDir> inDirectories;
    for(QFileInfo& inf : directory.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot))
        if(!inf.isDir()){
            std::cout << inf.filePath().toStdString() << " " << inf.size() << std::endl;
            statistic[path] += (static_cast<long long>(inf.size()));
        }
        else
            inDirectories.push_back(QDir(inf.filePath()));

    std::cout << "----------\n" << std::endl;
    for(QDir& dir : inDirectories)
        directoryTraversalBySize(dir, statistic);
}

void directoryTraversalByType(QDir directory, Statistic& statistic){
    std::string path = directory.absolutePath().toStdString();

    std::vector<QDir> inDirectories;
    for(QFileInfo& inf : directory.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot)){
        if(inf.isDir()) {
            inDirectories.push_back(QDir(inf.filePath()));
            continue;
        }

        std::string type = inf.suffix().toStdString();
        if(statistic.count(type) == 0)
            statistic[type] = static_cast<long long>(inf.size());
        else
            statistic[type] += (static_cast<long long>(inf.size()));
    }
    for(QDir& dir : inDirectories)
        directoryTraversalByType(dir, statistic);
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    /*
    Statistic statistic;
    directoryTraversalBySize(QDir::current(), statistic);

    for(auto x : statistic)
        std::cout << x.first << " " << x.second << std::endl;

    Statistic statistic2;
    directoryTraversalByType(QDir::current(), statistic2);

    for(auto x : statistic2)
        std::cout << x.first << " " << x.second << std::endl;
    */
    QTextStream cout(stdout);
    std::shared_ptr<TraversalStrategy> strategy = std::make_shared<BySizeTraversal>();
    auto res = strategy->execute(QDir::current().absolutePath());
    foreach(auto x , res.keys()){
        cout << x << " " << res[x] << Qt::endl;
    }
    app.exec();
}
