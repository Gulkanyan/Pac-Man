#include "Block.h"
#include <QBrush>

Block::Block(QGraphicsItem *parent): QGraphicsRectItem(parent){
    setRect(0,0,50,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::green);
    setBrush(brush);
}
