#include "drawmap.h"
#include <QGraphicsItem>
#include <QPoint>
#include <iostream>
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

void DrawBlock::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    cout << "Hello" << endl;
}


