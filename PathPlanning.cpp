#include "PathPlanning.h"
#include "drawmap.h"
#include <QGraphicsLineItem>
#include <QDebug>
#include <QThread>
#include <QElapsedTimer>
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
        tmp->append(QPointF(a->pos().x()-25,a->pos().y()-15));
        tmp->append(QPointF(a->pos().x()+25+50,a->pos().y()-15));
        tmp->append(QPointF(a->pos().x()+25+50,a->pos().y()+15+50));
        tmp->append(QPointF(a->pos().x()-25,a->pos().y()+15+50));
        tmp = this->mergeblock(tmp);
        boundingBlock.append(tmp);
    }
    foreach (QPolygonF *a , boundingBlock)
    {
        configurationSpace.append(new QGraphicsPolygonItem(*a));
        MyScene->addItem(configurationSpace.last());
    }
    boundingBlock.clear();
    foreach (DrawBlock* a , block)
    {
        QPolygonF *tmp = new QPolygonF();
        tmp->append(QPointF(a->pos().x()-27,a->pos().y()-17));
        tmp->append(QPointF(a->pos().x()+27+50,a->pos().y()-17));
        tmp->append(QPointF(a->pos().x()+27+50,a->pos().y()+17+50));
        tmp->append(QPointF(a->pos().x()-27,a->pos().y()+17+50));
        tmp = this->mergeblock(tmp);
        boundingBlock.append(tmp);
    }

}



QPolygonF* PathPlanning::mergeblock(QPolygonF *block)
{

    foreach(QPolygonF *a , boundingBlock)
    {

        if(block->intersects(*a))
         {
            //qDebug("helloo");
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
            tmp.append(p);
            node.append(tmp);
            QList<int> c;
            graph.append(c);
        }
    }

    for(int i = 0 ; i < node.length() ; i++)
    {
        graph[i].append(i);
    }

    for(int i = 0 ; i < node.length() ; i++)
    {

        for(int j = 0 ; j < node.length() ; j++)
        {
              if(i != j)
              {
                  if(!graph.at(i).contains(j))
                  {

                      QGraphicsLineItem *line = new QGraphicsLineItem;
                      line->setLine(node.at(i).x(),node.at(i).y(),node.at(j).x(),node.at(j).y());
                      MyScene->addItem(line);
                      if(line->collidingItems().isEmpty())
                      {
                          graph[i].append(j);
                          graph[j].append(i);

                       }
                       MyScene->removeItem(line);
                       delete line;
                  }

              }
        }
    }


}

void PathPlanning::startVisibility()
{
    for(int i = 0 ; i < graph.length() ; i++)
    {
        QGraphicsLineItem *line = new QGraphicsLineItem;
        line->setLine(start.x(),start.y(),node.at(i).x(),node.at(i).y());
        MyScene->addItem(line);
        if(line->collidingItems().isEmpty())
        {
            startVisibilitylist.append(i);
        }
        MyScene->removeItem(line);
        delete  line;
    }
}

void PathPlanning::endVisibility()
{
    node.append(end);
    QList<int> c;
    graph.append(c);
    graph.last().append(graph.length()-1);

    for(int i = 0 ; i < graph.length() - 1 ; i++)
    {
        QGraphicsLineItem *line = new QGraphicsLineItem;
        line->setLine(end.x(),end.y(),node.at(i).x(),node.at(i).y());
        MyScene->addItem(line);
        if(line->collidingItems().isEmpty())
        {
            graph[i].append(graph.length()-1);
        }
        MyScene->removeItem(line);
        delete  line;
    }
}

QPainterPath *PathPlanning::constructPath(QList<int> roadmap)
{
    QPainterPath *path = new QPainterPath;
    path->moveTo(start);
//    foreach(int a , roadmap)
//    {
//        path->lineTo(node.at(a));
//    }
    for(int a = 0 ; a < roadmap.length() ; a++)
    {
        if(a < roadmap.length() - 1)
        {
        QLineF line;
        line.setP1(path->currentPosition());
        line.setP2(node.at(roadmap.at(a)));
        line.setLength(line.length()-15);
        path->lineTo(line.p2());
        line.setP1(node.at(roadmap.at(a+1)));
        line.setP2(node.at(roadmap.at(a)));
        line.setLength(15);
        path->quadTo(node.at(roadmap.at(a)),line.p2());
        }
        else
        {
            path->lineTo(node.at(roadmap.at(a)));
        }
    }
    return path;
}


QPainterPath PathPlanning::findPath(QPointF startp,QPointF endp)
{

    QPainterPath *MyPath = new QPainterPath;
    this->endVisibility();
    this->startVisibility();
    QList<int> openset;
    qreal length = Q_INFINITY;
    qreal g = 0;
    qreal min = Q_INFINITY;
    int nodeShortIndex;
    for(int i = 0 ; i < startVisibilitylist.length() ; i++)
    {
        QLineF line ;
        line.setP1(node.at(startVisibilitylist.at(i)));
        line.setP2(end);
        qreal tmp = line.length();
        qDebug() << tmp << " + " << g << " < " << min << (tmp + g < min);
        if(tmp + g < min)
        {
            nodeShortIndex = startVisibilitylist.at(i);
            min = tmp + g;
        }

    }
    QLineF line ;
    line.setP1(start);
    line.setP2(node.at(nodeShortIndex));
     qDebug() << "g" << g;
    g = g + line.length();
     qDebug() << "g" << g;
    openset.append(nodeShortIndex);
    while (graph[openset.last()].length() > 1)
    {
        qDebug() << "-----------------------------------";
       min = Q_INFINITY;
       length = Q_INFINITY;
       qDebug() << graph[openset.last()];
        if(graph[openset.last()].contains(graph.last().first()))
        {
            openset.append(graph.last().first());
            break;
        }
        for(int i = 1 ; i < graph[openset.last()].length() ; i++)
        {
            if(openset.count(graph[openset.last()].at(i)))
            {
                continue;
            }
            QLineF line ;
            line.setP1(node.at(graph[openset.last()].at(i)));
            line.setP2(end);
            qreal tmp = line.length();
            tmp = tmp + line.length();
            qDebug() << tmp << " + " << g << " < " << min << (tmp + g < min);
            if(tmp + g < min)
            {
                nodeShortIndex = graph[openset.last()].at(i);
                min = tmp + g;
            }
        }
        QLineF line ;
        line.setP1(node.at(openset.last()));
        line.setP2(node.at(nodeShortIndex));
        g = g + line.length();
        qDebug() << "g" << g;
        openset.append(nodeShortIndex);
        qDebug() << "-----------------------------------";
    }
    MyPath = constructPath(openset);

    MyScene->addPath(*MyPath);
    foreach(QGraphicsPolygonItem *a , configurationSpace)
    {
        MyScene->removeItem(a);
    }
    return *MyPath;
}
void PathPlanning::pathFinding()
{
    constructGraph();
    findPath(this->start,this->end);
//    int i = graph.last().first();
//        for(int j = 1 ; j < graph.at(i).length() ; j++)
//        {
//            QGraphicsLineItem *line = new QGraphicsLineItem;
//            line->setLine(node.at(graph[i].at(0)).x(),node.at(graph[i].at(0)).y(),node.at(graph[i].at(j)).x(),node.at(graph[i].at(j)).y());
//            MyScene->addItem(line);
//        }
//    foreach (QGraphicsPolygonItem *a , configurationSpace)
//    {
//        MyScene->removeItem(a);
//    }
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
























