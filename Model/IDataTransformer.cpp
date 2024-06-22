#include "IDataTransformer.h"

QVector<QVector<QString>> DataTrasformer::transofrm(QMap<QString, double> &map)
{
    QVector<QVector<QString>> arr;
    foreach(auto x, map.keys()){
        QVector<QString> temp = {x, QString::number(map[x])};
        arr.push_back(temp);
    }
    return arr;
}
