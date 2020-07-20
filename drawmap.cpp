#include "drawmap.h"
#include <QGraphicsItem>
#include <QPoint>
#include <QGraphicsSceneMouseEvent>
#include <QLineF>
#include <QDebug>
DrawBlock::DrawBlock(CustomScene *Scene)
{
    this->setRect(0,0,50,50);
    this->setBrush(Qt::blue);
    this->setFlags(QGraphicsItem::ItemIsMovable);
    this->AddItemToScene(Scene);
    blockList.append(this);

}
QList<DrawBlock*> DrawBlock ::  blockList;
int DrawBlock::randomPos(int hi, int low)
{
    return (qrand() % ((hi + 1) - low) + low);
}

QVector<QPoint> DrawBlock::getVertex()
{
    QVector<QPoint> vertex ;
    vertex.append(QPoint(this->pos().x(),this->pos().y()));
    vertex.append(QPoint(this->pos().x()+50,this->pos().y()));
    vertex.append(QPoint(this->pos().x()+50,this->pos().y()+50));
    vertex.append(QPoint(this->pos().x(),this->pos().y()+50));

    return vertex;
}


void DrawBlock::AddItemToScene(CustomScene *Map)
{
    Map->addItem(this);
    this->setPos((int)this->randomPos(550,0)
                 ,(int)this->randomPos(550,0));
}

void DrawBlock::AddItemToScene(CustomScene *Map,QGraphicsItem *item)
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
}

void DrawBlock::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setBrush(Qt::blue);
}


