#include "Coin.h"

#include <QBrush>
#include "Core/CoreGlobals.h"
Coin::Coin(QGraphicsItem *parent): QObject(), QGraphicsRectItem(parent)
{
    setRect(0, 0, DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    QPixmap pixmapItem(":/images/Images/Point.png");
    pixmapItem = pixmapItem.scaled(QSize(DEFAULT_BLOCK_SIZE,DEFAULT_BLOCK_SIZE),  Qt::KeepAspectRatio);
    setBrush(QBrush(pixmapItem));
}

void Coin::SetPosition(int x, int y)
{
    this->setX(x);
    this->setY(y);
}
