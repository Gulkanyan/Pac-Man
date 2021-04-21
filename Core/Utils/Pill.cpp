#include "Pill.h"

#include <QBrush>
#include <CoreGlobals.h>
Pill::Pill(QGraphicsItem *parent): QObject(), QGraphicsRectItem(parent)
{
    setRect(0, 0, DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    QPixmap pixmapItem(":/images/Images/Pill.png");
    pixmapItem = pixmapItem.scaled(QSize(DEFAULT_BLOCK_SIZE,DEFAULT_BLOCK_SIZE),  Qt::KeepAspectRatio);
    setBrush(QBrush(pixmapItem));
}

void Pill::SetPosition(int x, int y)
{
    this->setX(x);
    this->setY(y);
}
