#ifndef MYSCENE_H
#define MYSCENE_H
#include <QGraphicsScene>

class MyScene:public CustomScene
{
public:
    MyScene();
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // MYSCENE_H
