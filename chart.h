#ifndef CHART_H
#define CHART_H


#include <QQuickPaintedItem>
#include <QPainter>

#include "graphdatamodel.h"

struct Label {
    QPointF position;
    QString text;
};

class Chart : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(double from READ from WRITE setFrom NOTIFY fromChanged)
    Q_PROPERTY(double to READ to WRITE setTo NOTIFY toChanged)
    Q_PROPERTY(double unit READ unit WRITE setUnit NOTIFY unitChanged)

    Q_PROPERTY(double aMul READ aMul WRITE setAMul NOTIFY mulChanged)
    Q_PROPERTY(double bMul READ bMul WRITE setBMul NOTIFY mulChanged)
    Q_PROPERTY(double cMul READ cMul WRITE setCMul NOTIFY mulChanged)

    Q_PROPERTY(int funcIndex WRITE setFuncIndex)
    Q_PROPERTY(GraphDataModel* model READ model)

public:


    explicit Chart(QQuickItem *parent = nullptr);
    virtual ~Chart() override;

    void paint(QPainter *painter) override;

    double from() const;
    double to() const;
    double unit() const;
    double aMul() const;
    double bMul() const;
    double cMul() const;

    GraphDataModel* model();

public slots:
    void setFrom(double from);
    void setTo(double to);
    void setUnit(double unit);

    void setAMul(double aMul);

    void setBMul(double bMul);

    void setCMul(double cMul);

    void setFuncIndex(int funcIndex);
    void updateGrid();

signals:
    void fromChanged(double from);
    void toChanged(double to);
    void unitChanged(double unit);

    void mulChanged(double aMul);


private:
    QVector<QPointF> m_chartData;
    QVector<QPointF> m_chartGrid;
    QVector<QPointF> m_chartGrid2;

    QList<int> m_gridVao;
    QList<int> m_gridVao2;

    double m_max = 25;
    double m_min = -25;

    double m_from = -1;
    double m_to = 10;
    double m_unit = 1;

    QList<Label*> m_labels;

    double m_aMul;
    double m_bMul;
    double m_cMul;

    GraphDataModel m_model;

    int m_funcIndex;

protected:
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;
};




#endif // CHART_H
