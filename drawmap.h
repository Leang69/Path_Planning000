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
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    QList<QGraphicsItem *> block;
    QList<QPoint> node;
    int top;
    int bottom;
    int left;
    int right;
};



#endif // DRAWMAP_H
