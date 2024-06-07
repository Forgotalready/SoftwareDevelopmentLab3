#include "BySizeTraversal.h"

void BySizeTraversal::directoryTraversal(QDir &directory, QMap<QString, double> &stat)
{
    QString path = directory.absolutePath();
    stat[path] = 0;

    std::vector<QDir> inDirectories;
    for(QFileInfo& inf : directory.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot))
        if(!inf.isDir())
            stat[path] += (static_cast<long long>(inf.size()));
        else
            inDirectories.push_back(QDir(inf.filePath()));

    for(QDir& dir : inDirectories)
        directoryTraversal(dir, stat);
}

void BySizeTraversal::formOtherGroup(QMap<QString, double> &stat, float pr)
{

}


QMap<QString, double> BySizeTraversal::execute(const QString &path)
{
    QDir directory;
    directory.setPath(path);
    QMap<QString, double> stat;

    directoryTraversal(directory, stat);

    double sum = 0.0;
    for(auto& x: stat)
        sum += x;


    for(auto& x : stat)
        x /= sum;


    return stat;
}
