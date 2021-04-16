#include "Player.h"
#include "StandardBlock.h"

#include "Utils/Coin.h"
#include "Utils/Pill.h"

#include <QPixmap>
#include <QSize>
#include <QBrush>

#include <QtDebug>

Player::Player(QGraphicsItem *parent): QObject(), QGraphicsEllipseItem(parent)
{
    setRect(1,1,48,48);
    QPixmap pixmapItem(":/images/Images/Right.png");
    pixmapItem = pixmapItem.scaled(QSize(48,48),  Qt::KeepAspectRatio);
    setBrush(QBrush(pixmapItem));

    m_currentStep = Step::First;

    stepSize = 10;
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

    setPos(pos().x() + stepSize, pos().y());

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

    setPos(pos().x() - stepSize, pos().y());


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

    setPos(pos().x(), pos().y() - stepSize);

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
    setPos(pos().x(), pos().y() + stepSize);

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

bool Player::IsCollided(Directions currentDirection)
{
    QList<QGraphicsItem*> cItems = this->collidingItems();

    for(int i = 0; i < cItems.size(); ++i)
    {
        // after transform to funcion
        StandardBlock* block = dynamic_cast<StandardBlock*>(cItems[i]);
        if(!block)
        {
            Coin* coin = dynamic_cast<Coin*>(cItems[i]);
            if(coin)
                delete coin;
            else
            {
                Pill* pill = dynamic_cast<Pill*>(cItems[i]);
                if(pill)
                    delete pill;
            }
            continue;
        }
        //

        if(currentDirection == Directions::Right)
            if(qreal(this->pos().x() + stepSize + 60) >= cItems.at(i)->pos().x()) // 60 is offset
            {
                this->setX(this->pos().x() - 10);
                return true;
            }

        if(currentDirection == Directions::Left)
            if(qreal(this->pos().x() - stepSize - 60) <= cItems.at(i)->pos().x())
            {
                this->setX(this->pos().x() + 10);
                return true;
            }

        if(currentDirection == Directions::Up)
            if(cItems.at(i)->pos().y() - this->pos().y() <= 0)     // <---      // after change the rest. Let it be as it is
            {
                this->setY(this->pos().y() + 10);
                return true;
            }

        if(currentDirection == Directions::Down)
            if(qreal(this->pos().y() + stepSize + 60) >= cItems.at(i)->pos().y())
            {
                this->setY(this->pos().y() - 10);
                return true;
            }
    }
    cItems.clear();
    return false;
}

int Player::GetStepSize()
{
    return stepSize;
}
