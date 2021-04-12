#include "Red.h"
#include <QBrush>

Red::Red(QGraphicsItem *parent): QGraphicsRectItem(parent){
    setRect(0,0,50,50);
    QPixmap pixmapItem(":/images/Images/Red.png");

    setBrush(QBrush(pixmapItem));

}
