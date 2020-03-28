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
    ui->BGenerate->setDisabled(true);
    ui->BstartPoint->setDisabled(true);
    ui->BendPoint->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BReset_clicked()
{
    ui->BGenerate->setDisabled(true);
    ui->BstartPoint->setDisabled(true);
    ui->BendPoint->setDisabled(true);
    Block->blockList.clear();
    Map->clear();

}

void MainWindow::on_Create_obstacle_clicked()
{
    ui->BstartPoint->setDisabled(false);
    Block = new DrawBlock(Map);
}


void MainWindow::on_BstartPoint_clicked()
{
    ui->BendPoint->setDisabled(true);
}

void MainWindow::on_BendPoint_clicked()
{

}
