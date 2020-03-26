#ifndef NODE_H
#define NODE_H
#include <QMultiHash>
#include <QList>
#include <QPoint>

class GrapNode
{
public:
    GrapNode();
    //QMultiHash<parentNode , childNode> Granerate(QList<QPoint *> node);
    QMultiHash<QPoint* , QPoint*> *Granerate(QList<QPoint *> node);  
};

#endif // NODE_H
