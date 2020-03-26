#include "GrapNode.h"

GrapNode::GrapNode()
{
    
}

QMultiHash<QPoint *, QPoint *> *GrapNode::Granerate(QList<QPoint *> node)
{
    QMultiHash<QPoint *, QPoint *> *GraphOfAllNode = new QMultiHash<QPoint *, QPoint *>;
    for(QPoint* a : node)
    {
        
    }
    return GraphOfAllNode;
}
