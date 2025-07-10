#include "line.h"
#include <QPainter>

Line::Line(QPointF point, QObject *parent) : Figure(point, parent)
{
}

Line::~Line()
{
}

void Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(penColor(), 2));
    painter->drawLine(startPoint(), endPoint());

    Q_UNUSED(option)
    Q_UNUSED(widget)
}
