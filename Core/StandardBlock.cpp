#include "StandardBlock.h"

#include <QBrush>

StandardBlock::StandardBlock(QGraphicsItem *parent): QObject(), QGraphicsRectItem(parent)
{
    setRect(0, 0, 50, 50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::gray);
    setBrush(brush);
}

void StandardBlock::SetPosition(int x, int y)
{
    this->setX(x);
    this->setY(y);
}
