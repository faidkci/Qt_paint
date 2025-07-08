#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

#include "paintscene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slotTimer();

    void on_actionRed_triggered();
    void on_actionGreen_triggered();
    void on_actionBlue_triggered();
    void on_actionClear_triggered();
    void on_actionCustomColor_triggered();
    void on_actionSave_triggered();
    void on_actionLoad_triggered();
    void on_actionSquare_triggered();
    void on_actionRomb_triggered();
    void on_actionTriangle_triggered();

private:
    Ui::MainWindow *ui;

    QTimer *timer;
    paintScene *scene;

    void resizeEvent(QResizeEvent * event);

};
#endif // MAINWINDOW_H
