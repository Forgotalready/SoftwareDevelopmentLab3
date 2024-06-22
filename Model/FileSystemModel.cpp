#include "FileSystemModel.h"


FileSystemModel::FileSystemModel(QMap<QString, double>&data, QObject *parent)
    : QAbstractItemModel(parent)
{
    transformer = std::make_shared<DataTrasformer>();
    m_data = transformer->transofrm(data);
}

int FileSystemModel::rowCount([[maybe_unused]] const QModelIndex &parent) const
{
    return m_data.count();
}

int FileSystemModel::columnCount([[maybe_unused]] const QModelIndex &) const
{
    return m_columns;
}

QVariant FileSystemModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole){
        return m_data[index.row()][index.column()];
    }
    return QVariant();
}

bool FileSystemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return 0;
}

QVariant FileSystemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Horizontal){
        return QString("Path" + QString::number(section));
    }else if(orientation == Qt::Vertical){
        return QString::number(section);
    }else{
        return QVariant();
    }
}

QModelIndex FileSystemModel::index(int row, int column, [[maybe_unused]] const QModelIndex &parent) const
{
    return createIndex(row, column, (void*)&(m_data[row][column]));
}

QModelIndex FileSystemModel::parent([[maybe_unused]] const QModelIndex &child) const
{
    return QModelIndex();
}
