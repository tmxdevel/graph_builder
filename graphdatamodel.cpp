#include "graphdatamodel.h"

#include <QVariant>

GraphDataModel::GraphDataModel(QObject *parent) : QAbstractListModel(parent)
{

}

GraphDataModel::~GraphDataModel()
{

}

QHash<int, QByteArray> GraphDataModel::roleNames() const
{
    QHash<int, QByteArray> result;
    result.insert(ValueX, "valueX");
    result.insert(ValueY, "valueY");
    return result;
}

int GraphDataModel::rowCount(const QModelIndex &parent) const
{
    return m_values.count();
}

QVariant GraphDataModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())return QVariant();
    if(role == ValueX) return QVariant::fromValue<double>(m_values.at(index.row()).x());
    if(role == ValueY) return QVariant::fromValue<double>(m_values.at(index.row()).y());
    return QVariant();
}

void GraphDataModel::clear()
{
    m_values.clear();
    updateData();
}

void GraphDataModel::addList(const QList<QPointF> &list)
{
    beginResetModel();
    m_values.append(list);
    endResetModel();
}

void GraphDataModel::stub()
{
    QList<QPointF> list;
    list << QPointF(1,1) << QPointF(1,2) << QPointF(2,1) << QPointF(2,2);
}

void GraphDataModel::updateData()
{
    beginResetModel();
    sort(0);
    endResetModel();
}


