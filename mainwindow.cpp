#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawmap.h"
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    Map = new QGraphicsScene();
    Block->AddBlockToScene(Map);
    Map->setSceneRect(0,0,1280,720);
    ui->setupUi(this);
    ui->View->setFixedSize(1280,720);
    ui->View->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->View->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->View->setScene(Map);
}

MainWindow::~MainWindow()
{
    delete ui;
}

