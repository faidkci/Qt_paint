#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
#include <QVector>
#include <QDataStream>

#include "figure.h"

class paintScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit paintScene(QObject *parent = 0);
    ~paintScene();

    void setPenColor(const QColor &color);
    QColor penColor() const { return m_penColor; }

    int typeFigure() const;
    void setTypeFigure(const int type);

    enum FigureType {
        SquareType,
        RombType,
        TriangleType,
        LineType,
        FreehandType
    };

    int type() const  { return Figure::FreehandType; }

    enum DrawMode {
        ModeDraw,
        ModeFigure,
        ModeFreehand
    };

    void setDrawMode(DrawMode mode);
    DrawMode drawMode() const;

    void clearScene();

    bool saveToFile(const QString &filename);
    bool loadFromFile(const QString &filename);

signals:
    void typeFigureChanged();

private:
    QPointF     previousPoint;
    QColor m_penColor = Qt::red;

    Figure *tempFigure = nullptr;
    int m_typeFigure;
    DrawMode m_drawMode = ModeDraw;

    QVector<Figure*> figures;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent * event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // PAINTSCENE_H
