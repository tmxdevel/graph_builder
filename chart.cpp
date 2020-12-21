#include "chart.h"

#include <QDebug>
#include <QtMath>
#include <QPointF>



Chart::Chart(QQuickItem *parent) : QQuickPaintedItem(parent)
{

    connect(this, &QQuickItem::widthChanged, this, &Chart::updateGrid);
    updateGrid();
    update();
}

Chart::~Chart()
{

}

void Chart::paint(QPainter *painter)
{
    QPen pen;
    painter->setRenderHint(QPainter::Antialiasing);

    int gridVaoOffset = 0;
    pen.setColor(QColor(60,62,61));
    pen.setWidth(1);
    for(auto cnt : m_gridVao2) {
        painter->setPen(pen);
        painter->drawPolyline(m_chartGrid2.constData() + gridVaoOffset, cnt);
        gridVaoOffset+=cnt;
    }

    gridVaoOffset = 0;
    pen.setColor(Qt::white);
    for(auto cnt : m_gridVao) {
        painter->setPen(pen);
        painter->drawPolyline(m_chartGrid.constData() + gridVaoOffset, cnt);
        gridVaoOffset+=cnt;
    }

    pen.setColor(Qt::red);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawPolyline(m_chartData.constData(), m_chartData.count());

}

double Chart::from() const
{
    return m_from;
}

void Chart::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    QQuickPaintedItem::geometryChanged(newGeometry, oldGeometry);
    update();
}

double Chart::to() const
{
    return m_to;
}

double Chart::unit() const
{
    return m_unit;
}

double Chart::aMul() const
{
    return m_aMul;
}

void Chart::setFrom(double from)
{
    qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_from, from))
        return;

    m_from = from;
    emit fromChanged(m_from);
    updateGrid();
    update();
}

void Chart::setTo(double to)
{
    qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_to, to))
        return;

    m_to = to;
    emit toChanged(m_to);
    updateGrid();
    update();
}

void Chart::setUnit(double unit)
{
    qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_unit, unit))
        return;

    m_unit = unit;
    emit unitChanged(m_unit);
    updateGrid();
    update();
}

void Chart::setAMul(double aMul)
{
    qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_aMul, aMul))
        return;

    m_aMul = aMul;
    emit mulChanged(m_aMul);
    updateGrid();
    update();
}

void Chart::setBMul(double bMul)
{
    qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_bMul, bMul))
        return;

    m_bMul = bMul;
    emit mulChanged(m_bMul);
    updateGrid();
    update();
}

void Chart::setCMul(double cMul)
{
    qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_cMul, cMul))
        return;

    m_cMul = cMul;
    emit mulChanged(m_cMul);
    updateGrid();
    update();
}

void Chart::setFuncIndex(int funcIndex)
{
    m_funcIndex = funcIndex;
    qDebug() << "Func index: " << funcIndex;
    updateGrid();
    update();
}

double f(double x) {
    return x;
}
double f2(double x) {
    return x*x;
}

void Chart::updateGrid()
{
    if(static_cast<int>(width()) == 0 || static_cast<int>(height()) == 0) return;
    if(m_from > m_to) return;


    // очищаем массивы точек для отрисовки осей и сетки
    m_chartGrid.clear();
    m_gridVao.clear();
    m_chartGrid2.clear();
    m_gridVao2.clear();
    m_labels.clear();

    m_min = 0;
    m_max = 0;
    MathFunctionX *func;
    switch (m_funcIndex) {
    case 0: func = new Sinusoid();
        break;
    case 1: func = new Logarithm();
        break;
    case 2: func = new Exponential();
        break;
    default:
        func = new Linear();
    }
    for(double i = m_from; i <= m_to; i+=m_unit) {
        double val = func->f(i,m_aMul,m_bMul,m_cMul);
        if(val > m_max) m_max = val;
        if(val < m_min) m_min = val;
    }
    m_max+=3;
    m_min -= 3;
    if(m_max-m_min>1000) {
        m_max=500;
        m_min=-500;
    }
    // конвертируем входные параметры в координаты окна
    double xScale = width() / (m_to - m_from);
    double yScale = height() / (m_max - m_min);

    double internalFrom = m_from * xScale;
    double internalTo = m_to * xScale;
    double internalUnitX = m_unit * xScale;
    double internalUnitY = m_unit * yScale;

    double internalMax = m_max * yScale;
    double internalMin = m_min * yScale;

    // Вычислим точку центра
    double centerX = -(internalFrom + (internalTo - internalFrom)/2);
    double centerY = (internalMin + (internalMax - internalMin)/2);

    double abscissaY = (centerY > height()/2 || centerY < -height()/2) ? height() - 20 : centerY + height()/2;
    double ordinateX = (centerX > width()/2 || centerX < -width()/2) ? 20 : centerX + width()/2;

    double yUnitStart = (centerY > height()/2 || centerY < -height()/2) ? (qFloor(internalMin/internalUnitY)*internalUnitY - internalUnitY) : centerY + height()/2;
    double xUnitStart = (centerX > width()/2 || centerX < -width()/2) ? (qFloor(internalFrom/internalUnitX)*internalUnitX - internalUnitX) : centerX + width()/2;

    for(double start = xUnitStart; start < width(); start += internalUnitX) {
        m_chartGrid2.append(QPointF(start,height()));
        m_chartGrid2.append(QPointF(start,0));
        m_gridVao2.append(2);
    }
    for(double start = xUnitStart; start > 0; start -= internalUnitX) {
        m_chartGrid2.append(QPointF(start,height()));
        m_chartGrid2.append(QPointF(start,0));
        m_gridVao2.append(2);
    }
    for(double start = yUnitStart; start < height(); start += internalUnitY) {
        m_chartGrid2.append(QPointF(0,start));
        m_chartGrid2.append(QPointF(width(),start));
        m_gridVao2.append(2);
    }
    for(double start = yUnitStart; start > 0; start -= internalUnitY) {
        m_chartGrid2.append(QPointF(0,start));
        m_chartGrid2.append(QPointF(width(),start));
        m_gridVao2.append(2);
    }

    for(double start = xUnitStart; start < width(); start += internalUnitX) {
        m_chartGrid.append(QPointF(start,abscissaY+3));
        m_chartGrid.append(QPointF(start,abscissaY-3));
        m_gridVao.append(2);
    }
    for(double start = xUnitStart; start > 0; start -= internalUnitX) {
        m_chartGrid.append(QPointF(start,abscissaY+3));
        m_chartGrid.append(QPointF(start,abscissaY-3));
        m_gridVao.append(2);
    }
    for(double start = yUnitStart; start < height(); start += internalUnitY) {
        m_chartGrid.append(QPointF(ordinateX+3,start));
        m_chartGrid.append(QPointF(ordinateX-3,start));
        m_gridVao.append(2);
    }
    for(double start = yUnitStart; start > 0; start -= internalUnitY) {
        m_chartGrid.append(QPointF(ordinateX+3,start));
        m_chartGrid.append(QPointF(ordinateX-3,start));
        m_gridVao.append(2);
    }

    m_chartGrid.append(QPointF(10,abscissaY));
    m_chartGrid.append(QPointF(width()-10,abscissaY));

    m_chartGrid.append(QPointF(width()-30,abscissaY-10));
    m_chartGrid.append(QPointF(width()-10,abscissaY));
    m_chartGrid.append(QPointF(width()-30,abscissaY+10));
    m_gridVao.append(5);

    m_chartGrid.append(QPointF(ordinateX,height()-10));
    m_chartGrid.append(QPointF(ordinateX,10));

    m_chartGrid.append(QPointF(ordinateX-10,30));
    m_chartGrid.append(QPointF(ordinateX,10));
    m_chartGrid.append(QPointF(ordinateX+10,30));
    m_gridVao.append(5);

    m_chartData.clear();
    double deltaX = (m_to - m_from) / width();
    for(int i = 0; i < width(); i+=3) {
        m_chartData.append(QPointF(i,-func->f(m_from+deltaX*i,m_aMul,m_bMul,m_cMul)*yScale + height()/2 + (m_max+m_min)/2*yScale));
    }
    delete func;
}

double Chart::bMul() const
{
    return m_bMul;
}

double Chart::cMul() const
{
    return m_cMul;
}
