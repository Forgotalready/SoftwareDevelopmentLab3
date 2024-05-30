#include <QDir>
#include <iostream>
#include <QCoreApplication>
#include <vector>
#include <unordered_map>

void directoryTraversal(QDir directory, std::unordered_map<std::string, long long>& statistic){
    std::string path = directory.absolutePath().toStdString();
    std::cout << path << std::endl;

    std::cout << "----------\n";

    statistic[path] = 0;

    std::vector<QDir> inDirectories;
    foreach(QFileInfo inf, directory.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot))
        if(!inf.isDir()){
            std::cout << inf.filePath().toStdString() << " " << inf.size() << std::endl;
            statistic[path] += (static_cast<long long>(inf.size()));
        }
        else
            inDirectories.push_back(QDir(inf.filePath()));

    std::cout << "----------\n" << std::endl;
    for(QDir& dir : inDirectories)
        directoryTraversal(dir, statistic);
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    std::unordered_map<std::string, long long> statistic;
    directoryTraversal(QDir::current(), statistic);

    for(auto x : statistic)
        std::cout << x.first << " " << x.second << std::endl;

    app.exec();
}
