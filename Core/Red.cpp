#include "Red.h"

#include <QBrush>

#include "Utils/Levels.h"
#include "CoreGlobals.h"

namespace
{
    int m_counter = 5;
    Directions m_movementDirection = Directions::Unknown;
}

Red::Red(QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    InitDefaultSettings();
}

void Red::InitDefaultSettings()
{
    setRect(0,0,50,50);
    QPixmap pixmapItem(":/red/Images/Red/RedEnemyDown.png");

    setBrush(QBrush(pixmapItem));

    this->setPos(350,350);
    SetPositions();
}

void Red::SetPositions()
{
    m_coordinates.x = this->pos().x() / DEFAULT_BLOCK_SIZE; // DEFAULT_BLOCK_SIZE means block size
    m_coordinates.y = this->pos().y() / DEFAULT_BLOCK_SIZE;
}

void Red::DoMove()
{
    if(m_counter == 0)
    {
        GetAvilableDirections();

        m_movementDirection = ChooseShorterWay();

        m_counter = 5;
    }

    switch (m_movementDirection)
    {
        case Directions::Up: MoveUp(); break;

        case Directions::Down: MoveDown(); break;

        case Directions::Right: MoveRight(); break;

        case Directions::Left: MoveLeft(); break;

        default: qDebug() << "Direction is uncnown"; m_counter--; break;
    }
}

void Red::GetAvilableDirections()
{
    m_availableDirections = {Directions::Left, Directions::Right, Directions::Down, Directions::Up};

    if(m_coordinates.x < CoreGlobals::playersCoords.x)
    {
        // left is blocked
        m_availableDirections.removeOne(Directions::Left);
    }

    if(m_coordinates.x > CoreGlobals::playersCoords.x)
    {
        // right is blocked
        m_availableDirections.removeOne(Directions::Right);
    }

    if(m_coordinates.y > CoreGlobals::playersCoords.y)
    {
        // down is blocked
        m_availableDirections.removeOne(Directions::Down);
    }

    if(m_coordinates.y < CoreGlobals::playersCoords.y)
    {
        // up is blocked
        m_availableDirections.removeOne(Directions::Up);
    }

    // Delete way if front is block
    int count = m_availableDirections.size();
    for(int i = 0; i < count; ++i)
    {
        if(m_availableDirections.at(i) == Directions::Up)
        {
            if(Levels::level.at(m_coordinates.y - 1).at(m_coordinates.x) == 1)
            {
                m_availableDirections.removeOne(Directions::Up);
                count--;
                i--;
                continue;
            }
        }
        if(m_availableDirections.at(i) == Directions::Down)
        {
            if(Levels::level.at(m_coordinates.y + 1).at(m_coordinates.x) == 1)
            {
                m_availableDirections.removeOne(Directions::Down);
                count--;
                i--;
                continue;
            }
        }
        if(m_availableDirections.at(i) == Directions::Right)
        {
            if(Levels::level.at(m_coordinates.y).at(m_coordinates.x + 1) == 1)
            {
                m_availableDirections.removeOne(Directions::Right);
                count--;
                i--;
                continue;
            }
        }
        if(m_availableDirections.at(i) == Directions::Left)
        {
            if(Levels::level.at(m_coordinates.y).at(m_coordinates.x - 1) == 1)
            {
                m_availableDirections.removeOne(Directions::Left);
                count--;
                i--;
                continue;
            }
        }
    }
}

Directions Red::ChooseShorterWay()
{
    if(m_availableDirections.size() == 1)
        return m_availableDirections.at(0);

    QMap<Directions, double> ways;

    for(int i = 0; i < m_availableDirections.size(); ++i)
    {
        if(m_availableDirections.at(i) == Directions::Up)
        {
            double x = std::abs(CoreGlobals::playersCoords.x - m_coordinates.x);
            double y = std::abs(CoreGlobals::playersCoords.y - (m_coordinates.y - 1));

            ways.insert(Directions::Up, sqrt(x * x + y * y));
        }
        if(m_availableDirections.at(i) == Directions::Down)
        {
            double x = std::abs(CoreGlobals::playersCoords.x - m_coordinates.x);
            double y = std::abs(CoreGlobals::playersCoords.y - (m_coordinates.y + 1));

            ways.insert(Directions::Down, sqrt(x * x + y * y));
        }
        if(m_availableDirections.at(i) == Directions::Right)
        {
            double x = std::abs(CoreGlobals::playersCoords.x - (m_coordinates.x + 1));
            double y = std::abs(CoreGlobals::playersCoords.y - m_coordinates.y);

            ways.insert(Directions::Right, sqrt(x * x + y * y));
        }
        if(m_availableDirections.at(i) == Directions::Left)
        {
            double x = std::abs(CoreGlobals::playersCoords.x - (m_coordinates.x - 1));
            double y = std::abs(CoreGlobals::playersCoords.y - m_coordinates.y);

            ways.insert(Directions::Left, sqrt(x * x + y * y));
        }
    }

    Directions movementDirection = Directions::Unknown;
    if((int)m_availableDirections.size() == 3)
    {
        if(ways.value(m_availableDirections.at(0)) < ways.value(m_availableDirections.at(1)))
        {
            if(ways.value(m_availableDirections.at(0)) < ways.value(m_availableDirections.at(2)))
            {
                movementDirection = m_availableDirections.at(0);
            }
            else
            {
                movementDirection = m_availableDirections.at(2);
            }
        }
        else if(ways.value(m_availableDirections.at(1)) < ways.value(m_availableDirections.at(2)))
        {
            movementDirection = m_availableDirections.at(1);
        }
        else
        {
            movementDirection = m_availableDirections.at(2);
        }
    }
    else if(m_availableDirections.size() == 2)
    {
        if(ways.value(m_availableDirections.at(0)) < ways.value(m_availableDirections.at(1)))
        {
            movementDirection = m_availableDirections.at(0);
        }
        else
        {
            movementDirection = m_availableDirections.at(1);
        }
    }

    return movementDirection;
}

void Red::MoveUp()
{
    setPos(pos().x(), pos().y() - 10);
    SetPositions();
    m_counter--;

    QPixmap pixmapItem(":/red/Images/Red/RedEnemyUp.png");
    setBrush(QBrush(pixmapItem));
}

void Red::MoveDown()
{
    setPos(pos().x(), pos().y() + 10);
    SetPositions();
    m_counter--;

    QPixmap pixmapItem(":/red/Images/Red/RedEnemyDown.png");
    setBrush(QBrush(pixmapItem));
}

void Red::MoveRight()
{
    setPos(pos().x() + 10, pos().y());
    SetPositions();
    m_counter--;

    QPixmap pixmapItem(":/red/Images/Red/RedEnemyRight.png");
    setBrush(QBrush(pixmapItem));
}

void Red::MoveLeft()
{
    setPos(pos().x() - 10, pos().y());
    SetPositions();
    m_counter--;

    QPixmap pixmapItem(":/red/Images/Red/RedEnemyLeft.png");
    setBrush(QBrush(pixmapItem));
}
