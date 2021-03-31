#include "Player.h"

#include <QBrush>

Player::Player(QGraphicsItem *parent): QObject(), QGraphicsEllipseItem(parent)
{
    setRect(0,0,100,100);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    setBrush(brush);
}
