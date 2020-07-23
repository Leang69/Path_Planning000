#ifndef TRAPZOIDALMAP_H
#define TRAPZOIDALMAP_H
#include <QList>
#include  <drawmap.h>
#include <QPainterPath>
#include <QGraphicsView>

class PathPlanning:public QObject
{
    Q_OBJECT
public:
    PathPlanning();
    PathPlanning(CustomScene *scene,QList<DrawBlock *> block,QGraphicsView *view);
    QList<QPointF> getCenterPointOfLine(QList<DrawBlock*> block);
    void offsetblock(QList<DrawBlock *> block);
    QPolygonF* mergeblock(QPolygonF *block);
    void constructGraph();
    void startVisibility();
    void endVisibility();


    QPainterPath *constructPath(QList<int> roadmap);
    void getAllLine(QList<DrawBlock *> block);
    void sortLine(QList<QGraphicsLineItem*> *setOfLine);
    QPainterPath findPath(QPointF start,QPointF end);
    QList<QGraphicsLineItem*> *AllLine = new QList<QGraphicsLineItem*>;
    QPointF getStart() const;
    QPointF getEnd() const;
    QPainterPath getMyPath() const;

public slots:
    void setStart();
    void setEnd();
    void pathFinding();
private:
    QPointF start,end;
    QGraphicsRectItem *startNode = new QGraphicsRectItem();
    QGraphicsRectItem *EndNode = new QGraphicsRectItem();
    CustomScene *MyScene;
    QPainterPath MyPath;
    QList<DrawBlock *> MyBlock;
    QList<QPolygonF *> boundingBlock;
    QList<QPointF> node;
    QList<QList<int>> graph;
    QList<int> startVisibilitylist;
    QList<QGraphicsPolygonItem *> configurationObstacle ;
    QGraphicsView *Myview;
};


#endif // TRAPZOIDALMAP_H
