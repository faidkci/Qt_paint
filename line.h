#ifndef LINE_H
#define LINE_H

#include "figure.h"

class Line : public Figure
{
    Q_OBJECT
public:
    explicit Line(QPointF point, QObject *parent = nullptr);
    ~Line();

    int type() const override { return Figure::LineType; }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // LINE_H
