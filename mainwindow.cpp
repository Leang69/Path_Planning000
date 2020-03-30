#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "drawmap.h"
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    Block->blockList.clear();
    Map->setSceneRect(0,0,600,600);
    ui->setupUi(this);
    ui->View->setFixedSize(600,600);
    ui->View->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->View->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->View->setScene(Map);
    ui->BstartPoint->setDisabled(true);
    ui->BendPoint->setDisabled(true);
    connect(this,&MainWindow::isStrat,Map,&CustomScene::isStartPoint);
    connect(this,&MainWindow::isEnd,Map,&CustomScene::isEndPoint);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BReset_clicked()
{
    ui->Create_obstacle->setDisabled(false);
    ui->BstartPoint->setDisabled(true);
    ui->BendPoint->setDisabled(true);
    Block->blockList.clear();
    delete PathMap;
    PathMap = new PathPlanning;
    Map->clear();

}

void MainWindow::on_Create_obstacle_clicked()
{
    Block = new DrawBlock(Map);
}


void MainWindow::on_BstartPoint_clicked()
{
    ui->BendPoint->setDisabled(false);
    emit this->isStrat();
}

void MainWindow::on_BendPoint_clicked()
{
    emit this->isEnd();
}

void MainWindow::on_BGenerate_clicked()
{
    ui->Create_obstacle->setDisabled(true);
    ui->BstartPoint->setEnabled(true);
    PathMap = new PathPlanning(Map,Block->blockList);
    connect(this,&MainWindow::pathFinding,PathMap,&PathPlanning::pathFinding);
    foreach(DrawBlock *a,Block->blockList)
    {
        a->setFlag(QGraphicsItem::ItemIsMovable,false);
    }
}

void MainWindow::on_BPathPlannig_clicked()
{
    emit this->pathFinding();
    Map->addPath(PathMap->getMyPath());
}
