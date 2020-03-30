#include "PathPlanning.h"
#include "drawmap.h"
#include <QGraphicsLineItem>
#include <QDebug>
#include <QThread>
#include <customscene.h>
PathPlanning::PathPlanning()
{

}

PathPlanning::PathPlanning(CustomScene *scene,QList<DrawBlock *> block)
{
   MyScene = scene;
   MyBlock = block;
   connect(MyScene,&CustomScene::chagendStartPos,this,&PathPlanning::setStart);
   connect(MyScene,&CustomScene::chagendEndtPos,this,&PathPlanning::setEnd);
   scene->addItem(startNode);
   scene->addItem(EndNode);

}

QList<QPointF> PathPlanning::getCenterPointOfLine(QList<DrawBlock *> block)
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

QPainterPath PathPlanning::findPath(QList<QPointF> Allnode,QPointF start,QPointF end)
{
    QList<int> pointINumber;
    int startIndex = 0;
    int endIndex = 1;
    foreach(QPointF a , Allnode)
    {
        if(start.x()*10000+start.y() <= a.x()*10000+a.y())
            break;
        else
            startIndex++;
    }
    foreach(QPointF a , Allnode)
    {
        if(end.x()*10000+end.y() <= a.x()*10000+a.y())
            break;
        else
            endIndex++;
    }

    Allnode.insert(startIndex,start); Allnode.insert(endIndex,end);
    if(startIndex > endIndex)
    {
        int tmp = startIndex;
        startIndex = endIndex;
        endIndex = tmp;
    }
    qDebug() << Allnode;
    qDebug() << "---------------------------------------------------";
    qDebug() << startIndex;
    qDebug() << endIndex;
    qDebug() << "---------------------------------------------------";
    QPainterPath *MyPath = new QPainterPath;
    MyPath->moveTo(Allnode.at(startIndex));
    QGraphicsLineItem *LinePath = new QGraphicsLineItem;
    QLineF *l1 = new QLineF;
    MyScene->addItem(LinePath);
    LinePath->setVisible(false);
    for(int i = startIndex ; i < endIndex ; i++)
    {
        l1->setLine(Allnode.at(i).x()+5,Allnode.at(i).y()+5,Allnode.at(endIndex).x()-5,Allnode.at(endIndex).y()-5);
        LinePath->setLine(*l1);
        qDebug() << "i" <<i;
        if(LinePath->collidingItems().length() == 0)
        {
            MyPath->lineTo(Allnode.at(endIndex));

        }
        else
        {

        }
    }
    return *MyPath;
}
void PathPlanning::pathFinding()
{

    MyPath = this->findPath(this->getCenterPointOfLine(MyBlock),this->start,this->end);
}

QPainterPath PathPlanning::getMyPath() const
{
    return MyPath;
}
void PathPlanning::setStart()
{
    start = MyScene->getcursorPos();
    qDebug() << "Start";
    startNode->setRect(start.x()-2.5,start.y()-2.5,5,5);
    startNode->setBrush(Qt::yellow);
}

void PathPlanning::setEnd()
{
    end = MyScene->getcursorPos();
    qDebug() << "End";
    EndNode->setRect(end.x()-2.5,end.y()-2.5,5,5);
    EndNode->setBrush(Qt::gray);
}



QPointF PathPlanning::getStart() const
{
    return start;
}

QPointF PathPlanning::getEnd() const
{
    return end;
}
























