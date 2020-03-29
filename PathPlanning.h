#ifndef TRAPZOIDALMAP_H
#define TRAPZOIDALMAP_H
#include <QList>
#include  <drawmap.h>

class PathPlanning
{
public:
    PathPlanning();
    PathPlanning(CustomScene *scene,QList<DrawBlock *> block);
    QList<QPointF> getPosPoint(QList<DrawBlock*> block);
    void getAllLine(QList<DrawBlock *> block);
    void sortLine(QList<QGraphicsLineItem*> *setOfLine);
    void findPath(QList<QPointF> Allnode,QPointF *start,QPointF *end);
    QList<QGraphicsLineItem*> *AllLine = new QList<QGraphicsLineItem*>;
    void setStart(const QPointF &value);
    void setEnd(const QPointF &value);
    QPointF getStart() const;
    QPointF getEnd() const;

private:
    QPointF start,end;
    CustomScene *MyScene;
};


#endif // TRAPZOIDALMAP_H
