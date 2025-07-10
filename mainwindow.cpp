#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QColorDialog>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QImageWriter>
#include <QImageReader>
#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , timer(nullptr)
    , scene(nullptr)
{
    ui->setupUi(this);

    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    scene = new paintScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::slotTimer);
    timer->start(100);
}

MainWindow::~MainWindow()
{
    delete scene;
    delete timer;
    delete ui;
}

void MainWindow::slotTimer()
{
    timer->stop();
    scene->setSceneRect(0,0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    timer->start(100);
    QWidget::resizeEvent(event);
}

void MainWindow::on_actionRed_triggered()
{
    scene->setPenColor(Qt::red);
    scene->setDrawMode(paintScene::ModeDraw);
}

void MainWindow::on_actionGreen_triggered()
{
    scene->setPenColor(Qt::green);
    scene->setDrawMode(paintScene::ModeDraw);
}

void MainWindow::on_actionBlue_triggered()
{
    scene->setPenColor(Qt::blue);
    scene->setDrawMode(paintScene::ModeDraw);
}

void MainWindow::on_actionClear_triggered()
{
    scene->clearScene();
}

void MainWindow::on_actionCustomColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, this, "Select Color");
    if (color.isValid()) {
        scene->setPenColor(color);
        scene->setDrawMode(paintScene::ModeDraw);
    }
}

void MainWindow::on_actionSquare_triggered()
{
    scene->setTypeFigure(paintScene::SquareType);
    scene->setDrawMode(paintScene::ModeFigure);
}

void MainWindow::on_actionRomb_triggered()
{
    scene->setTypeFigure(paintScene::RombType);
    scene->setDrawMode(paintScene::ModeFigure);
}

void MainWindow::on_actionTriangle_triggered()
{
    scene->setTypeFigure(paintScene::TriangleType);
    scene->setDrawMode(paintScene::ModeFigure);
}

void MainWindow::on_actionFreehand_triggered()
{
    scene->setDrawMode(paintScene::ModeFreehand);
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Save Vector Image", "",
                                                    "Vector Graphics (*.vec)");

    if (fileName.isEmpty()) return;

    if (!scene->saveToFile(fileName)) {
        QMessageBox::warning(this, "Save Error", "Failed to save file");
    }
}

void MainWindow::on_actionLoad_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Load Vector Image", "",
                                                    "Vector Graphics (*.vec)");

    if (fileName.isEmpty()) return;

    scene->clearScene();

    if (!scene->loadFromFile(fileName)) {
        QMessageBox::warning(this, "Load Error", "Failed to load file");
    }
}
