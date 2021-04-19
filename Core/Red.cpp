#include "Red.h"

#include <QBrush>
#include <QtDebug>

#include "Utils/Levels.h"
#include "CoreGlobals.h"

Red::Red(QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    InitDefaultSettings();
}

void Red::InitDefaultSettings()
{
    setRect(0,0,50,50);
    QPixmap pixmapItem(":/images/Images/Red.png");

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
    GetAvilableDirections();

    Directions movementDirection = ChooseShorterWay();

    switch (movementDirection)
    {
        case Directions::Up: setPos(pos().x(), pos().y() - 50); SetPositions(); break;

        case Directions::Down: setPos(pos().x(), pos().y() + 50); SetPositions(); break;

        case Directions::Right: setPos(pos().x() + 50, pos().y()); SetPositions(); break;

        case Directions::Left: setPos(pos().x() - 50, pos().y()); SetPositions(); break;

        default: qDebug() << "Direction is uncnown";
    }
}

void Red::GetAvilableDirections()
{
    m_availableDirections = {Directions::Left, Directions::Right, Directions::Up, Directions::Down};

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
            if(Levels::level.at(m_coordinates.x).at(m_coordinates.y - 1) == 1)
            {
                m_availableDirections.removeOne(Directions::Up);
                count--;
                i--;
                continue;
            }
        }
        if(m_availableDirections.at(i) == Directions::Down)
        {
            if(Levels::level.at(m_coordinates.x).at(m_coordinates.y + 1) == 1)
            {
                m_availableDirections.removeOne(Directions::Down);
                count--;
                i--;
                continue;
            }
        }
        if(m_availableDirections.at(i) == Directions::Right)
        {
            if(Levels::level.at(m_coordinates.x + 1).at(m_coordinates.y) == 1)
            {
                m_availableDirections.removeOne(Directions::Right);
                count--;
                i--;
                continue;
            }
        }
        if(m_availableDirections.at(i) == Directions::Left)
        {
            if(Levels::level.at(m_coordinates.x - 1).at(m_coordinates.y) == 1)
            {
                m_availableDirections.removeOne(Directions::Left);
                count--;
                i--;
                continue;
            }
        }
    }

#ifdef DEBUG_UTILS
    for(int i = 0; i < m_availableDirections.size(); ++i)
        qDebug() << "Avilable Directions [" << i << "] = " << m_availableDirections.at(i);
#endif
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

            qDebug() << "UP :::: " << sqrt(x * x + y * y);
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

    qDebug() << "Movement direction is <<< " << movementDirection;

    return movementDirection;
}
