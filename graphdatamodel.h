#ifndef GRAPHDATAMODEL_H
#define GRAPHDATAMODEL_H

#include <QAbstractListModel>
#include <QList>

class MathFunctionX {
    virtual double f(double x);
};

class GraphDataModel : public QAbstractListModel
{
public:
    explicit GraphDataModel(QObject *parent = nullptr);
    virtual ~GraphDataModel() override;

    QHash<int, QByteArray> roleNames()const override;
    int rowCount(const QModelIndex &parent = QModelIndex())const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole)const override;

private:

};

//class

#endif // GRAPHDATAMODEL_H
