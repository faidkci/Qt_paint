#include "paintscene.h"
#include "mainwindow.h"
#include "square.h"
#include "romb.h"
#include "triangle.h"
#include "line.h"
#include "freehand.h"
#include <qfiledevice.h>

paintScene::paintScene(QObject *parent) : QGraphicsScene(parent)
{
    tempFigure = nullptr;
    m_drawMode = ModeDraw;
    m_typeFigure = SquareType;
}

paintScene::~paintScene()
{
    clearScene();
}

void paintScene::setPenColor(const QColor &color)
{
    m_penColor = color;
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
    if (m_drawMode == ModeFreehand) {
        Freehand *freehand = new Freehand(event->scenePos());
        freehand->setPenColor(m_penColor);
        freehand->addPoint(event->scenePos());
        addItem(freehand);
        figures.append(freehand);
        tempFigure = freehand;
        previousPoint = event->scenePos();
    }
    else if (m_drawMode == ModeDraw) {
        Line *line = new Line(event->scenePos());
        line->setPenColor(m_penColor);
        addItem(line);
        figures.append(line);
        tempFigure = line;
    }
    else if (m_drawMode == ModeFigure) {
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
            tempFigure->setPenColor(m_penColor);
            addItem(tempFigure);
            figures.append(tempFigure);
        }
    }
}

void paintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_drawMode == ModeFreehand && tempFigure) {
        Freehand *freehand = dynamic_cast<Freehand*>(tempFigure);
        if (freehand) {
            freehand->addPoint(event->scenePos());
        }
    }
    else if (m_drawMode == ModeDraw && tempFigure) {
        Line *line = dynamic_cast<Line*>(tempFigure);
        if (line) {
            line->setEndPoint(event->scenePos());
        }
    }
    else if (m_drawMode == ModeFigure && tempFigure) {
        tempFigure->setEndPoint(event->scenePos());
    }
}

void paintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    tempFigure = nullptr;
}


// Загрузка фігур в текстовый файл
bool paintScene::saveToFile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);
    for (Figure *fig : figures) {
        int type = -1;
        if (dynamic_cast<Square *>(fig)) type = SquareType;
        else if (dynamic_cast<Romb *>(fig)) type = RombType;
        else if (dynamic_cast<Triangle *>(fig)) type = TriangleType;
        else if (dynamic_cast<Line *>(fig)) type = LineType;
        else if (dynamic_cast<Freehand *>(fig)) type = FreehandType;

        QColor c = fig->penColor();

        if (type == FreehandType) {
            // Обработка Freehand - сохраняем все точки
            Freehand *freehand = dynamic_cast<Freehand*>(fig);
            out << type << " " << freehand->getPoints().size();
            for (const QPointF &point : freehand->getPoints()) {
                out << " " << point.x() << " " << point.y() << " ";
            }
            out << " " << c.red() << " " << c.green() << " " << c.blue() << "\n";
        } else {
            // Обработка остальных фигур
            out << type << " "
                << fig->startPoint().x() << " " << fig->startPoint().y() << " "
                << fig->endPoint().x() << " " << fig->endPoint().y() << " "
                << c.red() << " " << c.green() << " " << c.blue() << "\n";
        }
    }
    file.close();
    return true;
}

// Загрузка фигур из файла
bool paintScene::loadFromFile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    while (!in.atEnd()) {
        int type;
        in >> type;

        if (type == FreehandType) {
            // Обработка Freehand
            int pointCount;
            in >> pointCount;

            QVector<QPointF> points;
            for (int i = 0; i < pointCount; i++) {
                qreal x, y;
                in >> x >> y;
                points.append(QPointF(x, y));
            }

            int r, g, b;
            in >> r >> g >> b;

            if (in.status() != QTextStream::Ok) break;

            if (!points.isEmpty()) {
                Freehand *freehand = new Freehand(points.first());
                for (int i = 1; i < points.size(); i++) {
                    freehand->addPoint(points[i]);
                }
                freehand->setPenColor(QColor(r, g, b));
                figures.append(freehand);
                addItem(freehand);
            }
        } else {
            // Обработка остальных фигур
            int r, g, b;
            qreal x1, y1, x2, y2;
            in >> x1 >> y1 >> x2 >> y2 >> r >> g >> b;

            if (in.status() != QTextStream::Ok) break;

            Figure *fig = nullptr;
            QPointF p1(x1, y1), p2(x2, y2);

            switch (type) {
            case SquareType:
                fig = new Square(p1);
                break;
            case RombType:
                fig = new Romb(p1);
                break;
            case TriangleType:
                fig = new Triangle(p1);
                break;
            case LineType:
                fig = new Line(p1);
                break;
            }

            if (fig) {
                fig->setStartPoint(p1);
                fig->setEndPoint(p2);
                fig->setPenColor(QColor(r, g, b));
                figures.append(fig);
                addItem(fig);
            }
        }
    }
    file.close();
    return true;
}

void paintScene::clearScene()
{
    for (Figure *figure : figures) {
        removeItem(figure);
        delete figure;
    }
    figures.clear();
    clear();
}
