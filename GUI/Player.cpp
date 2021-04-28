#include "Player.h"
#include "Utils/StandardBlock.h"

#include "Utils/Coin.h"
#include "Utils/Pill.h"
#include "Ghosts/Red.h"
#include "Ghosts/Blue.h"
#include "Ghosts/Orange.h"
#include "Ghosts/Purple.h"

#include <QPixmap>
#include <QSize>
#include <QBrush>

#include <QtDebug>
#include <QSound>

namespace
{
    Directions m_previousDirection = Directions::Up;
    int m_counter = 0;
    QSound m_eatfruit_sound(":/Sound/Music/pacman_eatfruit.wav");
    QSound m_death_sound(":/Sound/Music/pacman_death.wav");

}

Player::Player(QGraphicsItem *parent): QObject(), QGraphicsEllipseItem(parent)
{
    setRect(1, 1, DEFAULT_BLOCK_SIZE - 2, DEFAULT_BLOCK_SIZE - 2);
    QPixmap pixmapItem(":/pacman/Images/PacMan/RightClose.png");
    setBrush(QBrush(pixmapItem));

    m_currentStep = Step::First;
    stepSize = DEFAULT_BLOCK_SIZE / 5;

    m_score = 0;
    m_health = 5;

    m_IsMovementEnabled = true;
    m_directions = Directions::Up;
}

void Player::DoMovement()
{
    if(m_IsMovementEnabled == false)
        return;

    if(m_counter == 0)
    {
        m_previousDirection = m_directions;
        m_counter = 5;
    }

    if(m_previousDirection == Directions::Right)
    {
        if(IsCollided(Directions::Right))
        {
            m_IsMovementEnabled = false;
            m_counter = 0;
            return;
        }
        MoveRight();
        m_counter--;
    }
    else if(m_previousDirection == Directions::Left)
    {
        if(IsCollided(Directions::Left))
        {
            m_IsMovementEnabled = false;
            m_counter = 0;
            return;
        }
        MoveLeft();
        m_counter--;
    }
    else if(m_previousDirection == Directions::Up)
    {
        if(IsCollided(Directions::Up))
        {
            m_IsMovementEnabled = false;
            m_counter = 0;
            return;
        }
        MoveUp();
        m_counter--;
    }
    else if(m_previousDirection == Directions::Down)
    {
        if(IsCollided(Directions::Down))
        {
            m_IsMovementEnabled = false;
            m_counter = 0;
            return;
        }
        MoveDown();
        m_counter--;
    }
    else
        qDebug() << "Direction is unknown\n";
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

    if(pos().y() > 530)
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
                m_eatfruit_sound.play();

                m_score += 50;
                emit ScoreIsUpdated(m_score);
                delete coin;
            }
            else if(!coin)
            {
                Pill* pill = dynamic_cast<Pill*>(cItems[i]);
                if(pill)
                {
                    m_eatfruit_sound.play();
                    delete pill;
                    emit PillIsEaten();
                }
                else if(!pill)
                {
                    Red *red = dynamic_cast<Red*>(cItems[i]);
                    if(red)
                    {
                        if(red->GetState() == GhostsStates::Chase || red->GetState() == GhostsStates::Scattered)
                        {
                            m_death_sound.play();
                            m_health--;
                            emit HealthIsUpdated(m_health);

                            m_counter = 0;          //  start movement from first step
                            this->setPos(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
                        }

                        red->m_counter = 5;     //  start movement from first step
                        red->SetState(GhostsStates::Scattered);
                        red->setPos(9 * DEFAULT_BLOCK_SIZE, 9 * DEFAULT_BLOCK_SIZE);
                    }
                    else if(!red)
                    {
                        Blue * blue = dynamic_cast<Blue*>(cItems[i]);
                        if(blue)
                        {
                            if(blue->GetState() == GhostsStates::Chase || blue->GetState() == GhostsStates::Scattered)
                            {
                                m_death_sound.play();
                                m_health--;
                                emit HealthIsUpdated(m_health);

                                m_counter = 0;          //  start movement from first step
                                this->setPos(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
                            }

                            blue->m_counter = 5;
                            blue->SetState(GhostsStates::Scattered);
                            blue->setPos(10 * DEFAULT_BLOCK_SIZE, 10 * DEFAULT_BLOCK_SIZE);
                        }
                        else
                        {
                            Orange * orange = dynamic_cast<Orange*>(cItems[i]);
                            if(orange)
                            {
                                if(orange->GetState() == GhostsStates::Chase || orange->GetState() == GhostsStates::Scattered)
                                {
                                    m_death_sound.play();
                                    m_health--;
                                    emit HealthIsUpdated(m_health);

                                    m_counter = 0;          //  start movement from first step
                                    this->setPos(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
                                }

                                orange->m_counter = 5;
                                orange->SetState(GhostsStates::Scattered);
                                orange->setPos(9 * DEFAULT_BLOCK_SIZE, 10 * DEFAULT_BLOCK_SIZE);
                            }
                            else
                            {
                                Purple * purple = dynamic_cast<Purple*>(cItems[i]);
                                if(purple)
                                {
                                    if(purple->GetState() == GhostsStates::Chase || purple->GetState() == GhostsStates::Scattered)
                                    {
                                        m_death_sound.play();
                                        m_health--;
                                        emit HealthIsUpdated(m_health);

                                        m_counter = 0;          //  start movement from first step
                                        this->setPos(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
                                    }

                                    purple->m_counter = 5;
                                    purple->SetState(GhostsStates::Scattered);
                                    purple->setPos(10 * DEFAULT_BLOCK_SIZE, 9 * DEFAULT_BLOCK_SIZE);
                                }
                            }
                        }
                    }
                }
            }

            continue;
        }
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
