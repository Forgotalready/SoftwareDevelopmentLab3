#include "BySizeTraversal.h"

void BySizeTraversal::directoryTraversal(QDir &directory, QMap<QString, double> &stat)
{
    QString path = directory.absolutePath();
    stat[path] = 0;

    std::vector<QDir> inDirectories;
    for(QFileInfo& inf : directory.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot))
        if(!inf.isDir())
            stat[path] += (static_cast<double>(inf.size()));
        else
            inDirectories.push_back(QDir(inf.filePath()));

    for(QDir& dir : inDirectories)
        directoryTraversal(dir, stat);
}

QMap<QString, double> BySizeTraversal::execute(const QString &path)
{
    QDir directory;
    directory.setPath(path);
    QMap<QString, double> stat;

    directoryTraversal(directory, stat);

    return stat;
}
