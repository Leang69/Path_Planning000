#include "drawmap.h"
#include <QGraphicsItem>
#include <QPoint>
#include <QGraphicsSceneMouseEvent>
#include <QRectF>
#include <QDebug>
DrawBlock::DrawBlock()
{
    this->setRect(0,0,50,50);
    this->setBrush(Qt::blue);
    this->setFlags(QGraphicsItem::ItemIsMovable);
    blockList.append(this);
}
QList<DrawBlock*> DrawBlock ::  blockList;
int DrawBlock::randomPos(int hi, int low)
{
    return (qrand() % ((hi + 1) - low) + low);
}

void DrawBlock::AddBlockToScene(QGraphicsScene *Map)
{
    Map->addItem(this);
    this->setPos((int)this->randomPos(0,200)
                 ,(int)this->randomPos(0,200));
}

void DrawBlock::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
   this->setBrush(Qt::red);
   this->setPos(mapToScene(event->pos().x()-25,event->pos().y()-25));
    //this->setPos(event->pos().x()-25,event->pos().y()-25);
    Q_UNUSED(event);
}

void DrawBlock::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setBrush(Qt::blue);
    qDebug() << blockList.at(blockList.indexOf(this))->pos();
    Q_UNUSED(event);
}


