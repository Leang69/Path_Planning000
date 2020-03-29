#ifndef TRAPZOIDALMAP_H
#define TRAPZOIDALMAP_H
#include <QList>
#include  <drawmap.h>

class PathPlanning
{
public:
    PathPlanning();
    PathPlanning(QGraphicsScene *scene,QList<DrawBlock *> block);
    QList<QPointF> getPosPoint(QList<DrawBlock*> block);
    void getAllLine(QList<DrawBlock *> block);
    void sortLine(QList<QGraphicsLineItem*> *setOfLine);
    void findPath(QList<QPointF> Allnode,QPointF *start,QPointF *end);
    QList<QGraphicsLineItem*> *AllLine = new QList<QGraphicsLineItem*>;
};


#endif // TRAPZOIDALMAP_H
