#include "paintscene.h"
#include "square.h"
#include "romb.h"
#include "triangle.h"

paintScene::paintScene(QObject *parent) : QGraphicsScene(parent)
{
    tempFigure = nullptr;
    m_drawMode = ModeDraw;
    m_typeFigure = SquareType;
}

paintScene::~paintScene()
{

}

void paintScene::setPenColor(const QColor &color)
{
    penColor = color;
    setDrawMode(ModeDraw);
}

int paintScene::typeFigure() const
{
    return m_typeFigure;
}

void paintScene::setTypeFigure(const int type)
{
    m_typeFigure = type;
    setDrawMode(ModeFigure);
}

void paintScene::setDrawMode(DrawMode mode)
{
    m_drawMode = mode;
}

paintScene::DrawMode paintScene::drawMode() const
{
    return m_drawMode;
}

void paintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_drawMode == ModeDraw) {
        addEllipse(event->scenePos().x() - 5,
                   event->scenePos().y() - 5,
                   10,
                   10,
                   QPen(Qt::NoPen),
                   QBrush(penColor));
        previousPoint = event->scenePos();
    } else if (m_drawMode == ModeFigure) {
        if (tempFigure) {
            removeItem(tempFigure);
            delete tempFigure;
            tempFigure = nullptr;
        }
        switch (m_typeFigure) {
        case SquareType:
            tempFigure = new Square(event->scenePos());
            break;
        case RombType:
            tempFigure = new Romb(event->scenePos());
            break;
        case TriangleType:
            tempFigure = new Triangle(event->scenePos());
            break;
        }
        if (tempFigure) {
            tempFigure->setStartPoint(event->scenePos());
            tempFigure->setEndPoint(event->scenePos());
            tempFigure->setPenColor(penColor);
            addItem(tempFigure);
        }
    }
}

void paintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_drawMode == ModeDraw) {
        addLine(previousPoint.x(),
                previousPoint.y(),
                event->scenePos().x(),
                event->scenePos().y(),
                QPen(penColor, 10, Qt::SolidLine, Qt::RoundCap));
        previousPoint = event->scenePos();
    } else if (m_drawMode == ModeFigure && tempFigure) {
        tempFigure->setEndPoint(event->scenePos());
    }
}

void paintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_drawMode == ModeFigure && tempFigure) {
        tempFigure->setEndPoint(event->scenePos());
        tempFigure = nullptr;
    }
}


