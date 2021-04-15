#include "StandardBlock.h"

#include <QBrush>

StandardBlock::StandardBlock(QGraphicsItem *parent): QObject(), QGraphicsRectItem(parent)
{
    setRect(0, 0, 50, 50);
    QPixmap pixmapItem(":/images/Images/Rectangle.png");
    pixmapItem = pixmapItem.scaled(QSize(50,50),  Qt::KeepAspectRatio);
    setBrush(QBrush(pixmapItem));

}

void StandardBlock::SetPosition(int x, int y)
{
    this->setX(x);
    this->setY(y);
}
