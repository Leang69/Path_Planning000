#ifndef DRAWMAP_H
#define DRAWMAP_H
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QList>

class DrawBlock:public QGraphicsRectItem
{
public:
    DrawBlock(QGraphicsScene *Scene);
    QList<QGraphicsLineItem*> linelist;
    QGraphicsLineItem *line = new QGraphicsLineItem;
    int randomPos(int hi,int low);
    QList<QPointF*>* getVertex();
    QList<QGraphicsLineItem*> drawline();
    void AddItemToScene(QGraphicsScene *Map);
    void AddItemToScene(QGraphicsScene *Map,QGraphicsItem *item);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    static QList<DrawBlock*> blockList;
};



#endif // DRAWMAP_H
