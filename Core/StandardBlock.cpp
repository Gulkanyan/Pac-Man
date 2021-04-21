#include "StandardBlock.h"

#include <QBrush>
#include "CoreGlobals.h"
StandardBlock::StandardBlock(QGraphicsItem *parent): QObject(), QGraphicsRectItem(parent)
{
    setRect(0, 0, DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    QPixmap pixmapItem(":/images/Images/Rectangle.png");
    pixmapItem = pixmapItem.scaled(QSize(DEFAULT_BLOCK_SIZE,DEFAULT_BLOCK_SIZE),  Qt::KeepAspectRatio);
    setBrush(QBrush(pixmapItem));
}

void StandardBlock::SetPosition(int x, int y)
{
    this->setX(x);
    this->setY(y);
}
