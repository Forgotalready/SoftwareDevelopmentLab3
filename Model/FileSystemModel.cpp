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
    if(role != Qt::EditRole)
        return false;

    m_data[index.row()][index.column()] = value.String;
    emit dataChanged(index, index, {role});
    return true;
}

QVariant FileSystemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Horizontal){
        if(section == 0)
            return QString("Path");
        else if(section == 1)
            return QString("%");
        else
            return QVariant();
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

void FileSystemModel::setNewMap(QMap<QString, double>& data)
{
    m_data = transformer->transofrm(data);
    emit dataChanged(QModelIndex(), QModelIndex());
    emit headerDataChanged(Qt::Vertical, 0, m_data.size());
}
