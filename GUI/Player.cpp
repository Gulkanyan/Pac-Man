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

    m_currentStep = Step::First;
}


void Player::MoveRight()
{
    if(m_currentStep == Step::First)
    {
        SetRightImage();
        m_currentStep = Step::Second;
    }
    else
    {
        SetClosedRightImage();
        m_currentStep = Step::First;
    }

    setPos(pos().x() + 10, pos().y());


    if(pos().x() > 800)
        setPos(0, pos().y());
}

void Player::SetRightImage()
{
    QPixmap pixmapItem(":/images/Images/Right.png");
    setBrush(QBrush(pixmapItem));
}

void Player::SetClosedRightImage(){

    QPixmap pixmapItem(":/images/Images/Closed.png");
    setBrush(QBrush(pixmapItem));

}
void Player::MoveLeft()
{
    if(m_currentStep == Step::First)
    {
        SetLeftImage();
        m_currentStep = Step::Second;
    }
    else
    {
        SetClosedRightImage();
        m_currentStep = Step::First;
    }

    setPos(pos().x() - 10, pos().y());


    if(pos().x() < 0)
        setPos(800, pos().y());
}


void Player::MoveUp()
{
    if(m_currentStep == Step::First)
    {
        SetUpImage();
        m_currentStep = Step::Second;
    }
    else
    {
        SetClosedRightImage();
        m_currentStep = Step::First;
    }

    setPos(pos().x(), pos().y() - 10);

    if(pos().y() < 30)
        setPos(pos().x(), 800);
}

void Player::MoveDown()
{
    if(m_currentStep == Step::First)
    {
        SetDownImage();
        m_currentStep = Step::Second;
    }
    else
    {
        SetClosedRightImage();
        m_currentStep = Step::First;
    }
    setPos(pos().x(), pos().y() + 10);

    if(pos().y() > 800)
        setPos(pos().x(), 0);
}

void Player::SetLeftImage()
{
    QPixmap pixmapItem(":/images/Images/Left.png");
    setBrush(QBrush(pixmapItem));
}

void Player::SetUpImage()
{
    QPixmap pixmapItem(":/images/Images/Up.png");
    setBrush(QBrush(pixmapItem));
}

void Player::SetDownImage()
{
    QPixmap pixmapItem(":/images/Images/Down.png");
    setBrush(QBrush(pixmapItem));
}


