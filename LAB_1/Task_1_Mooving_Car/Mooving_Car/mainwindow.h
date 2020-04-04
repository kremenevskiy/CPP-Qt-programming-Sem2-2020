#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "rectangle.h"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QGraphicsScene *scene;

    QTimer *animationTimer;
    QTimer *sceneTimer;
    QTimer *generateTimer;

private:
    void resizeEvent(QResizeEvent *event);

private slots:
    void sceneUpdate();
    void Generate();

};
#endif // MAINWINDOW_H
