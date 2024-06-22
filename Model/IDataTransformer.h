#ifndef IDATATRANSFORMER_H
#define IDATATRANSFORMER_H

#include <QVector>
#include <QMap>

class IDataTransformer
{
public:
    IDataTransformer() = default;

    virtual ~IDataTransformer() = default;

    virtual QVector<QVector<QString>> transofrm(QMap<QString, double>&) = 0;
};

class DataTrasformer : public IDataTransformer{
    // IDataTransformer interface
public:
    QVector<QVector<QString> > transofrm(QMap<QString, double> &) override;
};

#endif // IDATATRANSFORMER_H
