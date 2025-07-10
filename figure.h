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
    enum FigureType {
        SquareType,
        RombType,
        TriangleType,
        LineType,
        FreehandType
    };

    explicit Figure(QPointF point, QObject *parent = 0);
    virtual ~Figure();


    virtual int type() const = 0;
    virtual void save(QDataStream &stream) const;
    virtual void load(QDataStream &stream);
    QPointF startPoint() const;
    QPointF endPoint() const;

    void setStartPoint(const QPointF point);
    void setEndPoint(const QPointF point);

    void setPenColor(const QColor &color);
    QColor penColor() const;

    virtual QRectF boundingRect() const override;

signals:
    void pointChanged();

protected:
    QPointF m_startPoint;
    QPointF m_endPoint;
    QColor m_penColor = Qt::black;

public slots:
    void updateRomb();
};

#endif // FIGURE_H
