#include <QDir>

#include <QTextStream>

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QDir myDir;
    QString info;
    myDir.setPath("C:/qtprojects");
    info = myDir.path();
    QFileInfo fileInfo(info);

    QTextStream cout(stdout);

    if(fileInfo.isDir()){
        QDir dir = fileInfo.dir();
        if(dir.cd(fileInfo.fileName())){
            foreach (QFileInfo inf, dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot, QDir::Type)) {
                QString temp = inf.fileName();
                cout << inf.fileName() << "---" << inf.size() << Qt::endl;
            }
        }
        dir.cdUp();
    }

    app.exec();
}
