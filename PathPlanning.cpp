#include "PathPlanning.h"
#include "drawmap.h"
#include <QGraphicsLineItem>
#include <QDebug>
#include <QThread>
PathPlanning::PathPlanning()
{

}

PathPlanning::PathPlanning(CustomScene *scene,QList<DrawBlock *> block)
{
   QList<QGraphicsRectItem*> *node = new QList<QGraphicsRectItem*>;
   foreach(QPointF a,getPosPoint(block))
   {
       node->append(new QGraphicsRectItem(a.x()-2.5,a.y()-2.5,5,5));
       scene->addItem(node->last());

   }
   MyScene = scene;
}

QList<QPointF> PathPlanning::getPosPoint(QList<DrawBlock *> block)
{
    QList<QPointF> AllCenterPoint;
    getAllLine(block);
    foreach(QGraphicsLineItem* a, *AllLine)
    {
        AllCenterPoint.append(a->line().center());
    }
    return AllCenterPoint;
}

void PathPlanning::getAllLine(QList<DrawBlock *> block)
{
    foreach(DrawBlock *a,block)
    {
        AllLine->append(a->linelist.at(0));
        AllLine->append(a->linelist.at(1));
        AllLine->append(a->linelist.at(2));
        AllLine->append(a->linelist.at(3));
    }
    sortLine(AllLine);
}

void PathPlanning::sortLine(QList<QGraphicsLineItem*> *setOfLine)
{
        int i, j;
        qreal key;
        for (i = 1; i < setOfLine->length(); i++)
        {
            key = setOfLine->at(i)->line().center().x() * 10000 + setOfLine->at(i)->line().center().y();
            j = i - 1;
            /* Move elements of arr[0..i-1], that are
            greater than key, to one position ahead
            of their current position */
            while (j >= 0 && (setOfLine->at(j)->line().center().x() * 10000 + setOfLine->at(j)->line().center().y() > key))
            {
                j = j - 1;
            }
            setOfLine->move(i,j+1);

        }
}

void PathPlanning::findPath(QList<QPointF> Allnode,QPointF *start,QPointF *end)
{
    QList<int> pointINumber; QList<int>::iterator startIndex,endIndex;
    foreach(QPointF a , Allnode)
    {
        pointINumber.append(a.x()*10000+a.y());
    }
    startIndex = qLowerBound(pointINumber.begin(),pointINumber.end(),start->toPoint().x()*10000+start->toPoint().y());
    endIndex = qUpperBound(pointINumber.begin(),pointINumber.end(),end->toPoint().x()*10000+end->toPoint().y());

}

void PathPlanning::setStart(const QPointF &value)
{
    start = value;
}

void PathPlanning::setEnd(const QPointF &value)
{
    end = value;
}

QPointF PathPlanning::getStart() const
{
    return start;
}

QPointF PathPlanning::getEnd() const
{
    return end;
}
























