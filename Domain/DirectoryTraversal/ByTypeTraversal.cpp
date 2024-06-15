#include "ByTypeTraversal.h"

void ByTypeTraversal::directoryTraversal(QDir &directory, QMap<QString, double> &stat)
{
    QString path = directory.absolutePath();

    std::vector<QDir> inDirectories;
    for(QFileInfo& inf : directory.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot)){
        if(inf.isDir()) {
            inDirectories.push_back(QDir(inf.filePath()));
            continue;
        }

        QString type = inf.suffix();
        if(stat.count(type) == 0)
            stat[type] = static_cast<double>(inf.size());
        else
            stat[type] += (static_cast<double>(inf.size()));
    }
    for(QDir& dir : inDirectories)
        directoryTraversal(dir, stat);
}

QMap<QString, double> ByTypeTraversal::execute(const QString &path)
{
    QDir directory;
    directory.setPath(path);
    QMap<QString, double> stat;

    directoryTraversal(directory, stat);

    return stat;
}
