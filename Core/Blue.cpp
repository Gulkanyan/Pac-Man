#include "Blue.h"
#include <QBrush>
#include "Core/CoreGlobals.h"
Blue::Blue(QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    setRect(0,0,DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    QPixmap pixmapItem(":/images/Images/Blue.png");
    setBrush(QBrush(pixmapItem));
}
