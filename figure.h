#ifndef FIGURE_H
#define FIGURE_H

#include <QObject>
#include <QGraphicsItem>
#include <QDebug>

class Figure : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF startPoint
                   READ startPoint WRITE setStartPoint
                       NOTIFY pointChanged)
    Q_PROPERTY(QPointF endPoint
                   READ endPoint WRITE setEndPoint
                       NOTIFY pointChanged)
public:
    explicit Figure(QPointF point, QObject *parent = 0);
    ~Figure();

    QPointF startPoint() const;
    QPointF endPoint() const;

    void setStartPoint(const QPointF point);
    void setEndPoint(const QPointF point);

    void setPenColor(const QColor &color);

    QColor WhatCa() const;

signals:
    void pointChanged();

private:
    QPointF m_startPoint;
    QPointF m_endPoint;
    QColor m_penColor = Qt::black;

    QRectF boundingRect() const;

public slots:
    void updateRomb();
};

#endif // FIGURE_H
