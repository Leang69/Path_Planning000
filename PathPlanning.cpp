#include "PathPlanning.h"
#include "drawmap.h"
#include <QGraphicsLineItem>
#include <QDebug>
#include <QThread>

#include <customscene.h>
PathPlanning::PathPlanning()
{

}

PathPlanning::PathPlanning(CustomScene *scene,QList<DrawBlock *> block,QGraphicsView *view)
{
   MyScene = scene;
   MyBlock = block;
   Myview = view;
   offsetblock(MyBlock);

   connect(MyScene,&CustomScene::chagendStartPos,this,&PathPlanning::setStart);
   connect(MyScene,&CustomScene::chagendEndtPos,this,&PathPlanning::setEnd);
   scene->addItem(startNode);
   scene->addItem(EndNode);

}



void PathPlanning::offsetblock(QList<DrawBlock *> block)
{
    foreach (DrawBlock* a , block)
    {
        QPolygonF *tmp = new QPolygonF();
        tmp->append(QPoint(a->pos().x()-25,a->pos().y()-15));
        tmp->append(QPoint(a->pos().x()+25+50,a->pos().y()-15));
        tmp->append(QPoint(a->pos().x()+25+50,a->pos().y()+15+50));
        tmp->append(QPoint(a->pos().x()-25,a->pos().y()+15+50));
        tmp = this->mergeblock(tmp);
        boundingBlock.append(tmp);
    }
    foreach (QPolygonF *a , boundingBlock)
    {

        configurationSpace.append(new QGraphicsPolygonItem(*a));
        MyScene->addItem(configurationSpace.last());
    }
    constructGraph();

}



QPolygonF* PathPlanning::mergeblock(QPolygonF *block)
{

    foreach(QPolygonF *a , boundingBlock)
    {

        if(block->intersects(*a))
         {
            qDebug("helloo");
            *block = block->united(*a);
            boundingBlock.removeOne(a);
         }
   }

    return block;
}

void PathPlanning::constructGraph()
{
    foreach (QPolygonF *a , boundingBlock)
    {
        foreach(QPointF p , a->toList())
        {
            QList<QPointF> tmp;
            tmp.append(Myview->mapToScene(p.toPoint()));
            graph.append(tmp);
        }
    }

    foreach(QList<QPointF> a ,graph)
    {
        foreach(QList<QPointF> b ,graph)
        {
            if(!a.contains(b.first()))
            {
                 QGraphicsLineItem *line = new QGraphicsLineItem;
                 line->setLine(a.first().rx(),a.first().ry(),b.first().rx(),b.first().ry());
                 MyScene->addItem(line);
                 qDebug() <<  line->collidingItems(Qt::ContainsItemShape).length();
                 if(
                       //not line->collidingItems().toSet().subtract(line->collidingItems(Qt::ContainsItemShape).toSet()).isEmpty()
                        line->collidingItems(Qt::ContainsItemShape).isEmpty()
                    )
                 {
                     a.append(b.first());
                     b.append(a.first());
                     delete line;
                 }
                 else
                 {
                     MyScene->removeItem(line);
                     delete line;
                 }
            }
        }
    }


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

void PathPlanning::constructGraph(QList<QPointF> getCenterPointOfLine)
{

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
        Allnode.move(startIndex,startIndex-1);
        Allnode.move(endIndex,endIndex-1);
        startIndex--;
        endIndex++;
    }
    qDebug() << Allnode;
    qDebug() << "---------------------------------------------------";
    qDebug() << startIndex;
    qDebug() << endIndex;
    qDebug() << "---------------------------------------------------";
    QPainterPath *MyPath = new QPainterPath;
    MyPath->moveTo(Allnode.at(startIndex));
    QGraphicsLineItem *LinePath = new QGraphicsLineItem;
    QGraphicsLineItem *LineTmp= new QGraphicsLineItem;
    QLineF *l1 = new QLineF;
    QLineF *l2 = new QLineF;
    MyScene->addItem(LinePath);
    MyScene->addItem(LineTmp);
    LinePath->setVisible(false);

    int sourceIndex = startIndex;
    int shortLength = 10000000;
    int shortIndex = startIndex;
    int x = Allnode.at(sourceIndex).x();

    l1->setLine(Allnode.at(sourceIndex).x()+5,Allnode.at(sourceIndex).y()+2.5,Allnode.at(endIndex).x()-5,Allnode.at(endIndex).y()-2.5);
    LinePath->setLine(*l1);
    if(LinePath->collidingItems().length() == 0)
    {
        MyPath->lineTo(Allnode.at(endIndex));
        return *MyPath;

    }

    for(int i = startIndex+1 ; i < endIndex ; i++)
    {
        /*l1->setLine(Allnode.at(sourceIndex).x()+5,Allnode.at(sourceIndex).y()+2.5,Allnode.at(endIndex).x()-5,Allnode.at(endIndex).y()-2.5);
         *
        LinePath->setLine(*l1);
        if(LinePath->collidingItems().length() == 0)
        {
            MyPath->lineTo(Allnode.at(endIndex));
            break;
        }
        else
        {

            if(Allnode.at(i).x() == x)
            {
                l1->setLine(Allnode.at(sourceIndex).x()+5,Allnode.at(sourceIndex).y()+2.5,Allnode.at(i).x()-5,Allnode.at(i).y()-2.5);
                l2->setLine(Allnode.at(sourceIndex).x()+5,Allnode.at(sourceIndex).y()+2.5,Allnode.at(endIndex).x()-5,Allnode.at(endIndex).y()-2.5);
                LinePath->setLine(*l1);
                int length = l1->length() + l2->length();
                if(shortLength > length && LinePath->collidingItems().length() == 0)
                {
                    shortLength = length;
                    shortIndex = i;
                }

            }
            else
            {
                MyPath->lineTo(Allnode.at(shortIndex));
                sourceIndex = shortIndex;
                l1->setLine(Allnode.at(sourceIndex).x()+5,Allnode.at(sourceIndex).y()+2.5,Allnode.at(i).x()-5,Allnode.at(i).y()-2.5);
                l2->setLine(Allnode.at(sourceIndex).x()+5,Allnode.at(sourceIndex).y()+2.5,Allnode.at(endIndex).x()-5,Allnode.at(endIndex).y()-2.5);
                LinePath->setLine(*l1);
                int length = l1->length() + l2->length();
                if(shortLength > length && LinePath->collidingItems().length() == 0)
                {
                    shortLength = length;
                    shortIndex = i;
                }
            }

        }*/

        l1->setLine(Allnode.at(sourceIndex).x()+5,Allnode.at(sourceIndex).y()+2.5,Allnode.at(endIndex).x()-5,Allnode.at(endIndex).y()-2.5);
        LinePath->setLine(*l1);
        if(LinePath->collidingItems().length() == 0 && Allnode.length() > 8)
        {
            MyPath->lineTo(Allnode.at(endIndex));
            break;
        }
        else
        {
            l1->setLine(Allnode.at(sourceIndex).x()+5,Allnode.at(sourceIndex).y()+2.5,Allnode.at(endIndex).x()-5,Allnode.at(endIndex).y()-2.5);
            if(Allnode.at(i).x() == x)
            {

                    l1->setLine(Allnode.at(sourceIndex).x(),Allnode.at(sourceIndex).y(),Allnode.at(i).x(),Allnode.at(i).y());
                    l2->setLine(Allnode.at(i).x(),Allnode.at(i).y(),Allnode.at(endIndex).x(),Allnode.at(endIndex).y());
                    LinePath->setLine(*l1);
                    int length = l2->length();
                    if(shortLength > length && LinePath->collidingItems().length() == 0)
                    {
                        shortLength = length;
                        shortIndex = i;
                    }
            }
            else
            {
                    MyPath->lineTo(Allnode.at(shortIndex));
                    sourceIndex = shortIndex;
                    shortLength = 10000000;
                    l1->setLine(Allnode.at(sourceIndex).x(),Allnode.at(sourceIndex).y(),Allnode.at(i).x(),Allnode.at(i).y());
                    l2->setLine(Allnode.at(i).x(),Allnode.at(i).y(),Allnode.at(endIndex).x(),Allnode.at(endIndex).y());
                    LinePath->setLine(*l1);
                    int length = l2->length();
                    if(shortLength > length && LinePath->collidingItems().length() == 0)
                    {
                        shortLength = length;
                        shortIndex = i;
                    }
            }
        }

    }
    MyPath->lineTo(Allnode.at(endIndex));
    return *MyPath;
}
void PathPlanning::pathFinding()
{


}



QPainterPath PathPlanning::getMyPath() const
{
    return MyPath;
}
void PathPlanning::setStart()
{
    start = MyScene->getcursorPos();
    qDebug() << "Start";
    startNode->setRect(start.x()-7,start.y()+2.5,5,5);
    startNode->setBrush(Qt::yellow);
}

void PathPlanning::setEnd()
{
    end = MyScene->getcursorPos();
    qDebug() << "End";
    EndNode->setRect(end.x()+1,end.y()+2.5,5,5);
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
























