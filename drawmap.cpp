#include "drawmap.h"
#include <QGraphicsItem>
#include <QPoint>
#include <QGraphicsSceneMouseEvent>
#include <QRectF>
#include <QDebug>
DrawBlock::DrawBlock()
{
    this->setRect(0,0,50,50);
    this->setFlags(QGraphicsItem::ItemIsMovable);
    block.append(this);
}

void DrawBlock::AddBlockToScene(QGraphicsScene *Map)
{
    Map->addItem(block.last());
}

void DrawBlock::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
  this->setPos(mapToScene(event->pos()));
  qDebug() << this->pos().x() << this->pos().y();
}


