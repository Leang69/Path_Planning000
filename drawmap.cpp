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
QList<QGraphicsItem *> DrawBlock ::  blockList;
int DrawBlock::randomPos(int hi, int low)
{
    return (qrand() % ((hi + 1) - low) + low);
}

void DrawBlock::AddBlockToScene(QGraphicsScene *Map)
{
    Map->addItem(blockList.last());
    this->setPos((int)this->randomPos(0,200)
                 ,(int)this->randomPos(0,200));
}

void DrawBlock::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
   this->setBrush(Qt::red);
   this->setPos(mapToScene(event->pos().x()-25,event->pos().y()-25));
}

void DrawBlock::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setBrush(Qt::blue);
    qDebug() << this->pos().x() << this->pos().y();
}


