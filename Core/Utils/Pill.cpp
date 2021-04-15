#include "Pill.h"

#include <QBrush>

Pill::Pill(QGraphicsItem *parent): QObject(), QGraphicsRectItem(parent)
{
    setRect(0, 0, 50, 50);
    QPixmap pixmapItem(":/images/Images/Pill.png");
    pixmapItem = pixmapItem.scaled(QSize(50,50),  Qt::KeepAspectRatio);
    setBrush(QBrush(pixmapItem));
}

void Pill::SetPosition(int x, int y)
{
    this->setX(x);
    this->setY(y);
}
