#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawmap.h"
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    Map = new QGraphicsScene();
    Block->blockList.clear();
    Map->setSceneRect(0,0,600,600);
    ui->setupUi(this);
    ui->View->setFixedSize(600,600);
    ui->View->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->View->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->View->setScene(Map);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BReset_clicked()
{
    Block->blockList.clear();
    Map->clear();
}

void MainWindow::on_Create_obstacle_clicked()
{
    Block = new DrawBlock(Map);
}

