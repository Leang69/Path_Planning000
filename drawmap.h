#ifndef DRAWMAP_H
#define DRAWMAP_H
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QList>
#include "customscene.h"

class DrawBlock:public QGraphicsRectItem
{
public:
    DrawBlock(CustomScene *Scene);
    int randomPos(int hi,int low);
    QVector<QPoint> getVertex();
    void AddItemToScene(CustomScene *Map);
    void AddItemToScene(CustomScene *Map,QGraphicsItem *item);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    static QList<DrawBlock*> blockList;
    QVector<QPoint> vertex;
};



#endif // DRAWMAP_H
