#include "freehand.h"
#include <QPainter>
#include <algorithm>

Freehand::Freehand(QPointF point, QObject *parent) : Figure(point, parent)
{
    points.append(point);
    setStartPoint(point);
    setEndPoint(point);
}

Freehand::~Freehand()
{
}

void Freehand::addPoint(QPointF point)
{
    points.append(point);
    setEndPoint(point);
    prepareGeometryChange();
}

void Freehand::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(penColor(), 2));

    if (points.size() > 1) {
        for (int i = 0; i < points.size() - 1; ++i) {
            painter->drawLine(points[i], points[i+1]);
        }
    }

    Q_UNUSED(option)
    Q_UNUSED(widget)
}

QRectF Freehand::boundingRect() const
{
    qreal minX = std::numeric_limits<qreal>::max();
    qreal minY = std::numeric_limits<qreal>::max();
    qreal maxX = std::numeric_limits<qreal>::min();
    qreal maxY = std::numeric_limits<qreal>::min();

    for (const QPointF &p : points) {
        minX = qMin(minX, p.x());
        minY = qMin(minY, p.y());
        maxX = qMax(maxX, p.x());
        maxY = qMax(maxY, p.y());
    }

    return QRectF(minX, minY, maxX - minX, maxY - minY).adjusted(-5, -5, 5, 5);
}

void Freehand::save(QDataStream &stream) const
{
    Figure::save(stream);
    stream << points;
}

void Freehand::load(QDataStream &stream)
{
    Figure::load(stream);
    stream >> points;
}
