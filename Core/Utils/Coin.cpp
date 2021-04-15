#include "Coin.h"

#include <QBrush>

Coin::Coin(QGraphicsItem *parent): QObject(), QGraphicsRectItem(parent)
{
    setRect(0, 0, 50, 50);
    QPixmap pixmapItem(":/images/Images/Point.png");
    pixmapItem = pixmapItem.scaled(QSize(50,50),  Qt::KeepAspectRatio);
    setBrush(QBrush(pixmapItem));
}

void Coin::SetPosition(int x, int y)
{
    this->setX(x);
    this->setY(y);
}
