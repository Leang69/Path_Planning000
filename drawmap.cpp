#include "drawmap.h"
#include <QGraphicsItem>
#include <QPoint>
#include <QGraphicsSceneMouseEvent>
#include <QLineF>
#include <QDebug>
DrawBlock::DrawBlock(QGraphicsScene *Scene)
{
    this->setRect(0,0,50,50);
    this->setBrush(Qt::blue);
    linelist.append(new QGraphicsLineItem());
    linelist.append(new QGraphicsLineItem());
    linelist.append(new QGraphicsLineItem());
    linelist.append(new QGraphicsLineItem());
    this->setFlags(QGraphicsItem::ItemIsMovable);
    this->AddItemToScene(Scene);
    foreach(QGraphicsItem *a,linelist)
    {
        this->AddItemToScene(Scene,a);
        a->setVisible(false);
    }
    blockList.append(this);
    foreach(DrawBlock *a , blockList)
    {
        a->drawline();
    }

}
QList<DrawBlock*> DrawBlock ::  blockList;
int DrawBlock::randomPos(int hi, int low)
{
    return (qrand() % ((hi + 1) - low) + low);
}



QList<QPointF*>* DrawBlock::getVertex()
{
    QList<QPointF*> *tmp = new QList<QPointF*> ;
    tmp->append(new QPointF(this->pos()));//vertex top left
    tmp->append(new QPointF(this->pos().x()+50,this->pos().y()));//vertex top right
    tmp->append(new QPointF(this->pos().x(),this->pos().y()+50));//vertex top right
    tmp->append(new QPointF(this->pos().x()+50,this->pos().y()+50));//vertex top right
    return tmp;

}

QList<QGraphicsLineItem*> DrawBlock::drawline()
{
    QLineF line1 , line2 , line3 ,line4;
    line1.setLine(getVertex()->at(0)->x()
                 ,getVertex()->at(0)->y()-1
                 ,getVertex()->at(0)->x()
                 ,1);
    line2.setLine(getVertex()->at(1)->x()
                 ,getVertex()->at(1)->y()-1
                 ,getVertex()->at(1)->x()
                 ,1);
    line3.setLine(getVertex()->at(2)->x()
                 ,getVertex()->at(2)->y()+1
                 ,getVertex()->at(2)->x()
                 ,599);
    line4.setLine(getVertex()->at(3)->x()
                 ,getVertex()->at(3)->y()+1
                 ,getVertex()->at(3)->x()
                 ,599);
    linelist.at(0)->setLine(line1);
    linelist.at(1)->setLine(line2);
    linelist.at(2)->setLine(line3);
    linelist.at(3)->setLine(line4);
    trimLine();
    return linelist;

}

void DrawBlock::trimLine()
{
    QLineF line;
    QGraphicsItem *tmpItem;
    if(linelist.at(0)->collidingItems().length() != 0)
    {
        qreal tmp = 0;
        foreach(QGraphicsItem *a , linelist.at(0)->collidingItems())
        {
            if(a->y() > tmp)
            {
                tmp = a->y();
                tmpItem = a;
            }
        }
        line.setLine(linelist.at(0)->line().p1().x()
                     ,linelist.at(0)->line().p1().y()
                     ,linelist.at(0)->line().p1().x()
                     ,tmp + 50);
        linelist.at(0)->setLine(line);
    }
    if(linelist.at(1)->collidingItems().length() != 0)
    {
        int tmp = 0;
        foreach(QGraphicsItem *a , linelist.at(1)->collidingItems())
        {
            if(a->y() > tmp)
            {
                tmp = a->y();
            }
        }
        line.setLine(linelist.at(1)->line().p1().x()
                     ,linelist.at(1)->line().p1().y()
                     ,linelist.at(1)->line().p1().x()
                     ,tmp + 50);
        linelist.at(1)->setLine(line);
    }
    if(linelist.at(2)->collidingItems().length() != 0)
    {
        int tmp = 1000000000;
        foreach(QGraphicsItem *a , linelist.at(2)->collidingItems())
        {
            if(a->y() < tmp)
            {
                tmp = a->y();
            }
        }
        line.setLine(linelist.at(2)->line().p1().x()
                     ,linelist.at(2)->line().p1().y()
                     ,linelist.at(2)->line().p1().x()
                     ,tmp);
        linelist.at(2)->setLine(line);
    }
    if(linelist.at(3)->collidingItems().length() != 0)
    {
        int tmp = 1000000000;
        foreach(QGraphicsItem *a , linelist.at(3)->collidingItems())
        {
            if(a->y() < tmp)
            {
                tmp = a->y();
            }
        }
        line.setLine(linelist.at(3)->line().p1().x()
                     ,linelist.at(3)->line().p1().y()
                     ,linelist.at(3)->line().p1().x()
                     ,tmp);
        linelist.at(3)->setLine(line);
    }
}

void DrawBlock::AddItemToScene(QGraphicsScene *Map)
{
    Map->addItem(this);
    this->setPos((int)this->randomPos(550,0)
                 ,(int)this->randomPos(550,0));
}

void DrawBlock::AddItemToScene(QGraphicsScene *Map,QGraphicsItem *item)
{
    Map->addItem(item);
}

void DrawBlock::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
   if( (mapToScene(event->pos()).x() >= 25 && mapToScene(event->pos()).x() <= 575) && (mapToScene(event->pos()).y() >= 25 && mapToScene(event->pos()).y() <= 575)  )
   {
   this->setBrush(Qt::red);
   this->setPos(mapToScene(event->pos().x()-25,event->pos().y()-25));
   }
    Q_UNUSED(event);
}

void DrawBlock::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setBrush(Qt::blue);
    foreach(DrawBlock *a , blockList)
    {
        a->drawline();
    }
    Q_UNUSED(event);
}


