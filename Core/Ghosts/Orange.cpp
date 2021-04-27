#include "Orange.h"
#include <QBrush>
#include <CoreGlobals.h>
Orange::Orange(Ghost *parent): Ghost(parent)
{
    setRect(0,0,DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    QPixmap pixmapItem(":/images/Images/Orange.png");

    setBrush(QBrush(pixmapItem));


}
