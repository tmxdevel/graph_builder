#ifndef GRAPHDATAMODEL_H
#define GRAPHDATAMODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QHash>
#include <QtMath>

class MathFunctionX {
public:
    virtual ~MathFunctionX() {};
    virtual double f(double x, double a, double b, double c){return x;};
};

class GraphDataModel : public QAbstractListModel
{
public:
    enum GraphRoles {
        Value
    };

    explicit GraphDataModel(QObject *parent = nullptr);
    virtual ~GraphDataModel() override;

    QHash<int, QByteArray> roleNames()const override;
    int rowCount(const QModelIndex &parent = QModelIndex())const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole)const override;

    void registerFunction(const QByteArray &name, MathFunctionX *funcObj);

public slots:
    void updateData();
    void setBounds(double x, double y);
    void setFunction(const QString &name);

private:
    QHash<QByteArray, MathFunctionX*> m_funcObjects;
    QList<double> m_values;

    double m_fromX = -100;
    double m_toX = 100;
    double m_unit = 10;
    QString m_funcName;
};

class Linear : public MathFunctionX
{
public:
    explicit Linear(){};
    virtual ~Linear() override {};
    virtual double f(double x, double a, double b, double c) override {return x;};
};

class Sinusoid : public MathFunctionX
{
public:
    explicit Sinusoid(){};
    virtual ~Sinusoid() override {};
    virtual double f (double x, double a, double b, double c) override {return a + b*qSin(x + c);};
};

class Logarithm : public MathFunctionX
{
public:
    explicit Logarithm(){};
    virtual ~Logarithm() override {};
    virtual double f (double x, double a, double b, double c) override {return a + b*qLn(x + c);};
};

class Exponential : public MathFunctionX
{
public:
    explicit Exponential(){};
    virtual ~Exponential() override {};
    virtual double f (double x, double a, double b, double c) override {return a + b*qPow(qCos(x),-c*x);};
};



#endif // GRAPHDATAMODEL_H
