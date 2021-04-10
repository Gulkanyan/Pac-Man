#include "Player.h"

#include <QPixmap>
#include <QSize>
#include <QBrush>

Player::Player(QGraphicsItem *parent): QObject(), QGraphicsEllipseItem(parent)
{
    setRect(0,0,50,50);
    QPixmap pixmapItem(":/images/Images/Right.png");
    pixmapItem = pixmapItem.scaled(QSize(50,50),  Qt::KeepAspectRatio);

    setBrush(QBrush(pixmapItem));
}

void Player::MoveRight()
{
    if(m_state != Position::Right)
        SetRightImage();

    setPos(pos().x() + 10, pos().y());

    if(pos().x() > 800)
        setPos(0, pos().y());
}

void Player::MoveLeft()
{
    if(m_state != Position::Left)
        SetLeftImage();

    setPos(pos().x() - 10, pos().y());

    if(pos().x() < 0)
        setPos(800, pos().y());
}

void Player::MoveUp()
{
    if(m_state != Position::Left)
        SetUpImage();

    setPos(pos().x(), pos().y() - 10);

    if(pos().y() < 0)
        setPos(pos().x(), 800);
}

void Player::MoveDown()
{
    if(m_state != Position::Left)
        SetDownImage();

    setPos(pos().x(), pos().y() + 10);

    if(pos().y() > 800)
        setPos(pos().x(), 0);
}
void Player::SetRightImage()
{
    QPixmap pixmapItem(":/images/Images/Right.png");
    pixmapItem = pixmapItem.scaled(QSize(50,50),  Qt::KeepAspectRatio);
    setBrush(QBrush(pixmapItem));
}
void Player::SetLeftImage()
{
    QPixmap pixmapItem(":/images/Images/Left.png");
 //   pixmapItem = pixmapItem.scaled(QSize(50,50),  Qt::KeepAspectRatio);
    setBrush(QBrush(pixmapItem));
}

void Player::SetUpImage()
{
    QPixmap pixmapItem(":/images/Images/Up.png");
   // pixmapItem = pixmapItem.scaled(QSize(50,50),  Qt::KeepAspectRatio);
    setBrush(QBrush(pixmapItem));
}

void Player::SetDownImage()
{
    QPixmap pixmapItem(":/images/Images/Down.png");
  //  pixmapItem = pixmapItem.scaled(QSize(50,50),  Qt::KeepAspectRatio);
    setBrush(QBrush(pixmapItem));
}
