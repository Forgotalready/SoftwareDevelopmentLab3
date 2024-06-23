#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QMap>
#include <memory>

#include "IDataTransformer.h"

class FileSystemModel final: public QAbstractItemModel
{
    Q_OBJECT
public:
    FileSystemModel(QMap<QString, double>& ,QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
private:
    std::shared_ptr<IDataTransformer> transformer;
    QVector<QVector<QString>> m_data;
    int m_columns = 2;
public slots:
    void setNewMap(QMap<QString, double>&);
};
#endif // FILESYSTEMMODEL_H
