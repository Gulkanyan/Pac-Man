#include "Blue.h"
#include <QBrush>

Blue::Blue(QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    setRect(0,0,50,50);
    QPixmap pixmapItem(":/images/Images/Blue.png");
    setBrush(QBrush(pixmapItem));
}
