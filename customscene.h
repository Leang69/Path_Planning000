#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H
#include <QGraphicsScene>

class CustomScene:public QGraphicsScene
{
    Q_OBJECT
public:
    CustomScene();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QPointF getcursorPos();
signals:
    void chagendStartPos(QPointF start);
    void chagendEndtPos(QPointF start);
private:
    QPointF cursorPos;
};

#endif // CUSTOMSCENE_H
