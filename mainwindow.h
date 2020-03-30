#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "drawmap.h"
#include "PathPlanning.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void isStrat();
    void isEnd();
    void pathFinding();
private slots:
    void on_Create_obstacle_clicked();

    void on_BReset_clicked();

    void on_BstartPoint_clicked();

    void on_BendPoint_clicked();

    void on_BGenerate_clicked();

    void on_BPathPlannig_clicked();

private:
    bool isStartB = false;
    bool isEndB = false;
    QGraphicsRectItem *startnode,*endnode;
    DrawBlock *Block;
    PathPlanning *PathMap;
    CustomScene *Map  = new CustomScene();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
