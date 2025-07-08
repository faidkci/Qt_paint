#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QColorDialog>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QImageWriter>
#include <QImageReader>

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
    timer->stop();
    delete scene;

    scene = new paintScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    timer->start(100);
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

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    "Save Image", "",
                                                    "PNG Image (*.png);;JPEG Image (*.jpg *.jpeg);;Bitmap Image (*.bmp)");

    if (fileName.isEmpty()) return;

    QRectF rect = scene->itemsBoundingRect();
    QPixmap pixmap(rect.size().toSize());
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    scene->render(&painter, pixmap.rect(), rect);

    if (!pixmap.save(fileName)) {
        QMessageBox::warning(this, "Save Error", "Failed to save image file");
    }
}

void MainWindow::on_actionLoad_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Load Image", "",
                                                    "Image Files (*.png *.jpg *.jpeg *.bmp)");

    if (fileName.isEmpty()) return;

    timer->stop();
    delete scene;

    scene = new paintScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    timer->start(100);

    QPixmap pixmap(fileName);
    if (pixmap.isNull()) {
        QMessageBox::warning(this, "Load Error", "Failed to load image file");
        return;
    }

    QGraphicsPixmapItem* item = scene->addPixmap(pixmap);
    item->setPos(0, 0);

    scene->setSceneRect(scene->itemsBoundingRect());
}


