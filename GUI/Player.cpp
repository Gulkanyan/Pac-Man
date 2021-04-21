#include "Player.h"
#include "StandardBlock.h"

#include "Utils/Coin.h"
#include "Utils/Pill.h"
#include "Red.h"
#include "Blue.h"
#include "Orange.h"
#include "Purple.h"

#include <QPixmap>
#include <QSize>
#include <QBrush>

#include <QtDebug>

Player::Player(QGraphicsItem *parent): QObject(), QGraphicsEllipseItem(parent)
{
    setRect(1, 1, DEFAULT_BLOCK_SIZE - 2, DEFAULT_BLOCK_SIZE - 2);
    QPixmap pixmapItem(":/pacman/Images/PacMan/RightClose.png");
    setBrush(QBrush(pixmapItem));

    m_currentStep = Step::First;
    stepSize = DEFAULT_BLOCK_SIZE / 5;

    m_score = 0;
    m_health = 5;
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

    if(pos().x() > 470)
        setPos(0, pos().y());
}

void Player::SetRightImage()
{
    QPixmap pixmapItem(":/pacman/Images/PacMan/RightOpen.png");
    setBrush(QBrush(pixmapItem));
}

void Player::SetClosedRightImage()
{
    QPixmap pixmapItem(":/pacman/Images/PacMan/RightClose.png");
    setBrush(QBrush(pixmapItem));
}

void Player::SetLeftImage()
{
    QPixmap pixmapItem(":/pacman/Images/PacMan/LeftOpen.png");
    setBrush(QBrush(pixmapItem));
}

void Player::SetClosedLeftImage()
{
    QPixmap pixmapItem(":/pacman/Images/PacMan/LeftClose.png");
    setBrush(QBrush(pixmapItem));
}

void Player::SetUpImage()
{
    QPixmap pixmapItem(":/pacman/Images/PacMan/UpOpen.png");
    setBrush(QBrush(pixmapItem));
}

void Player::SetClosedUpImage()
{
    QPixmap pixmapItem(":/pacman/Images/PacMan/UpClose.png");
    setBrush(QBrush(pixmapItem));
}

void Player::SetDownImage()
{
    QPixmap pixmapItem(":/pacman/Images/PacMan/DownOpen.png");
    setBrush(QBrush(pixmapItem));
}

void Player::SetClosedDownImage()
{
    QPixmap pixmapItem(":/pacman/Images/PacMan/DownClose.png");
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
        setPos(470, pos().y());
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

    if(pos().y() < 0)
        setPos(pos().x(), 550);
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

    if(pos().y() > 500)
        setPos(pos().x(), 0);
}

bool Player::IsCollided(Directions currentDirection)
{
    QList<QGraphicsItem*> cItems = this->collidingItems();

    for(int i = 0; i < cItems.size(); ++i)
    {
        // during movement
        StandardBlock* block = dynamic_cast<StandardBlock*>(cItems[i]);

        if(!block)
        {
            Coin* coin = dynamic_cast<Coin*>(cItems[i]);
            if(coin)
            {
                m_score += 50;
                emit ScoreIsUpdated(m_score);
                delete coin;
            }
            else if(!coin)
            {
                Pill* pill = dynamic_cast<Pill*>(cItems[i]);
                if(pill)
                    delete pill;
                else if(!pill)
                {
                    Red *red = dynamic_cast<Red*>(cItems[i]);
                    Orange * orange = dynamic_cast<Orange*>(cItems[i]);
                    Blue * blue = dynamic_cast<Blue*>(cItems[i]);
                    Purple * purple = dynamic_cast<Purple*>(cItems[i]);
                    if(red || orange || blue || purple)
                    {

                        m_health--;
                        emit HealthIsUpdated(m_health);
                        this->setPos(25, 25);
                        red->setPos(225,250);
//                        orange->setPos(250,250);
//                        purple->setPos(250,275);
                        //blue->setPos(225,275);

                    }
                }
            }

            continue;
        }
        //

        if(currentDirection == Directions::Right)
            if(qreal(this->pos().x() + stepSize + 35) >= cItems.at(i)->pos().x()) // 60 is offset
            {
                this->setX(this->pos().x() - DEFAULT_BLOCK_SIZE / 5);
                return true;
            }

        if(currentDirection == Directions::Left)
            if(qreal(this->pos().x() - stepSize - 35) <= cItems.at(i)->pos().x())
            {
                this->setX(this->pos().x() + DEFAULT_BLOCK_SIZE / 5);
                return true;
            }

        if(currentDirection == Directions::Up)
            if(cItems.at(i)->pos().y() - this->pos().y() <= 0)     // <---      // after change the rest. Let it be as it is
            {
                this->setY(this->pos().y() + DEFAULT_BLOCK_SIZE / 5);
                return true;
            }

        if(currentDirection == Directions::Down)
            if(qreal(this->pos().y() + stepSize + 35) >= cItems.at(i)->pos().y())
            {
                this->setY(this->pos().y() - DEFAULT_BLOCK_SIZE / 5);
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
