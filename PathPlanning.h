#ifndef TRAPZOIDALMAP_H
#define TRAPZOIDALMAP_H
#include <QList>
#include  <drawmap.h>
#include <QPainterPath>

class PathPlanning:public QObject
{
    Q_OBJECT
public:
    PathPlanning();
    PathPlanning(CustomScene *scene,QList<DrawBlock *> block);
    QList<QPointF> getCenterPointOfLine(QList<DrawBlock*> block);
    void getAllLine(QList<DrawBlock *> block);
    void sortLine(QList<QGraphicsLineItem*> *setOfLine);
    void constructGraph (QList<QPointF> getCenterPointOfLine);
    QPainterPath findPath(QList<QPointF> Allnode,QPointF start,QPointF end);
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
};


#endif // TRAPZOIDALMAP_H
