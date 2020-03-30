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
    void chagendStartPos();
    void chagendEndtPos();
public slots:
    void isStartPoint();
    void isEndPoint();
private:
    bool isStart;
    QPointF cursorPos;
};

#endif // CUSTOMSCENE_H
