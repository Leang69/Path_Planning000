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
    int randomPos(int hi,int low);
    void AddBlockToScene(QGraphicsScene *Map);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    static QList<QGraphicsItem *> blockList;
    QList<QPoint> node;
    int top;
    int bottom;
    int left;
    int right;
};



#endif // DRAWMAP_H
