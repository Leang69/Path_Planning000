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
    qDebug() << cursorPos;
}


QPointF CustomScene::getcursorPos()
{
    return cursorPos;
}
