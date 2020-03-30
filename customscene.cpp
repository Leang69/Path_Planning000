#include "customscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include "drawmap.h"
CustomScene::CustomScene()
{

}

void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    cursorPos =  event->scenePos();
    QGraphicsScene::mousePressEvent(event);
    if(this->isStart)
    emit chagendStartPos();
    else
    emit chagendEndtPos();
}


QPointF CustomScene::getcursorPos()
{
    return cursorPos;
}

void CustomScene::isStartPoint()
{
    this->isStart = true;
}

void CustomScene::isEndPoint()
{
    this->isStart = false;
}
