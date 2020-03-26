#include "drawmap.h"
#include <QGraphicsItem>
#include <QPoint>
#include <iostream>
using namespace :: std;
DrawBlcok::DrawBlcok()
{
    QGraphicsRectItem *tmpRect = new QGraphicsRectItem;
    tmpRect->setRect(100,100,500,500);
    tmpRect->setFlags(QGraphicsItem::ItemIsMovable);
    block.append(tmpRect);
    //dfadsfsdfasdfadsfdsfghjkdfghjdfgvh
}

void DrawBlcok::AddBlockToScene(QGraphicsScene *Map)
{
    Map->addItem(block.last());
}

void DrawBlcok::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    cout << "Hello" << endl;
}


