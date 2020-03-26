#ifndef DRAWMAP_H
#define DRAWMAP_H
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QList>
#include <QPoint>

class DrawBlock:public QGraphicsRectItem
{
public:
    DrawBlock();
    void AddBlockToScene(QGraphicsScene *Map);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QList<QGraphicsItem *> block;
    QList<QPoint *> node;
    QPoint *point;
};



#endif // DRAWMAP_H
