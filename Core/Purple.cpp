#include "Purple.h"
#include <QBrush>

Purple::Purple(QGraphicsItem *parent): QGraphicsRectItem(parent){
    setRect(0,0,50,50);
    QPixmap pixmapItem(":/images/Images/Orange.png");

    setBrush(QBrush(pixmapItem));

}
