#ifndef STANDARDBLOCK_H
#define STANDARDBLOCK_H

#include <QGraphicsRectItem>

class StandardBlock : public QObject, public QGraphicsRectItem
{
public:
    StandardBlock(QGraphicsItem* parent = NULL);

    void SetPosition(int, int);
};

#endif // STANDARDBLOCK_H
