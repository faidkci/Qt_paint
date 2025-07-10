#ifndef FREEHAND_H
#define FREEHAND_H

#include "figure.h"
#include <QVector>

class Freehand : public Figure
{
    Q_OBJECT
public:
    explicit Freehand(QPointF point, QObject *parent = nullptr);
    ~Freehand();

    void addPoint(QPointF point);
    int type() const override { return Figure::FreehandType; }

    // Добавим метод для получения точек
    const QVector<QPointF>& getPoints() const { return points; }

    void save(QDataStream &stream) const override;
    void load(QDataStream &stream) override;

    QRectF boundingRect() const override;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QVector<QPointF> points;
};

#endif // FREEHAND_H
