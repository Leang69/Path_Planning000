#include "drawmap.h"
#include <QGraphicsItem>
#include <QPoint>
#include <iostream>
#include <QGraphicsSceneMouseEvent>
using namespace :: std;
DrawBlock::DrawBlock()
{
    this->setRect(100,100,500,500);
    this->setFlags(QGraphicsItem::ItemIsMovable);
    block.append(this);
    //dfadsfsdfasdfadsfdsfghjkdfghjdfgvh
}

void DrawBlock::AddBlockToScene(QGraphicsScene *Map)
{
    Map->addItem(block.last());
}

void DrawBlock::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
        cout << "Goodbye" << endl;
}


