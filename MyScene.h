#ifndef SCENE_H
#define SCENE_H
#include <QGraphicsScene>

class MyScene: public QGraphicsScene
{
public:
    MyScene();
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
};

#endif // SCENE_H
