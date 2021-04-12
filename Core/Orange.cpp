#include "Orange.h"
#include <QBrush>

Orange::Orange(QGraphicsItem *parent): QGraphicsRectItem(parent){
    setRect(0,0,50,50);
    QPixmap pixmapItem(":/images/Images/Orange.png");

    setBrush(QBrush(pixmapItem));

}
