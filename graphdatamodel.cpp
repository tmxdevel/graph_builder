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
    result.insert(Value, "value");
    return result;
}

int GraphDataModel::rowCount(const QModelIndex &parent) const
{
    return m_values.count();
}

QVariant GraphDataModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())return QVariant();
    if(role == Value) return QVariant::fromValue<double>(m_values.at(index.row()));
    return QVariant();
}

void GraphDataModel::registerFunction(const QByteArray &name, MathFunctionX *funcObj)
{

}

void GraphDataModel::updateData()
{

}

void GraphDataModel::setBounds(double x, double y)
{

}

void GraphDataModel::setFunction(const QString &name)
{

}


