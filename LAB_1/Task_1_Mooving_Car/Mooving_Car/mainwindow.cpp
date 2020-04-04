#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "car.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    //ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    animationTimer = new QTimer;
    animationTimer->start(1000/80);
    sceneTimer = new QTimer;
    sceneTimer->start(100);

    generateTimer = new QTimer;
    generateTimer->start(2000);

// Обновление зоны сцены
    connect(sceneTimer, SIGNAL(timeout()), this, SLOT(sceneUpdate()));

// Перемещение объекта
    connect(animationTimer, SIGNAL(timeout()), scene, SLOT(advance()));

// Появление объекта
    connect(generateTimer, SIGNAL(timeout()), this, SLOT(Generate()));
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::sceneUpdate(){
    sceneTimer->stop();
    scene->setSceneRect(0, 0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);

}


void MainWindow::Generate(){

    scene->addItem(new Car(rand() % (ui->graphicsView->height() - 150)));

}



void MainWindow::resizeEvent(QResizeEvent *event){
    sceneTimer->start(100);
    QMainWindow::resizeEvent(event);
}
