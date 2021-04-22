#include "Red.h"

#include <QBrush>

#include "Utils/Levels.h"
#include "CoreGlobals.h"

namespace
{
    Directions m_movementDirection = Directions::Unknown;
    bool m_onScatteringLoop = false;
    int m_scatteringStep = 0;
}

Red::Red(QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    InitDefaultSettings();
}

void Red::InitDefaultSettings()
{
    setRect(0,0,DEFAULT_BLOCK_SIZE,DEFAULT_BLOCK_SIZE);
    QPixmap pixmapItem(":/red/Images/Red/RedEnemyDown.png");
    pixmapItem = pixmapItem.scaled(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    setBrush(QBrush(pixmapItem));

    this->setPos(350,350);
    SetPositions();

    m_state = GhostsStates::Chase;
    m_counter = 5;
}

void Red::SetPositions()
{
    m_coordinates.x = this->pos().x() / DEFAULT_BLOCK_SIZE; // DEFAULT_BLOCK_SIZE means block size
    m_coordinates.y = this->pos().y() / DEFAULT_BLOCK_SIZE;
}

void Red::DoMove()
{
    qDebug() << "*/*/*/*//*/*/*/*/*/* x = " << m_coordinates.x << " y = " << m_coordinates.y;
    if(m_counter == 0)
    {
        if(m_state == GhostsStates::Chase)
        {
            qDebug() << "Choose Directions for Chase mode";
            DisableScatteredLoop();

            GetAvialableDirections(CoreGlobals::playersCoords.x, CoreGlobals::playersCoords.y);
            m_movementDirection = ChooseShorterWay();
        }
        else if(m_state == GhostsStates::Scattered)
        {
            qDebug() << "Choose Directions for Scattered mode";
            if(m_coordinates.x == 17 && m_coordinates.y == 1)
                m_onScatteringLoop = true;

            if(m_onScatteringLoop)
                ScatteredLoop();
            else
            {
                GetAvialableDirections(17, 1);
                m_movementDirection = ChooseScatteredShorterWay(17, 1);
            }
        }
        else if(m_state == GhostsStates::Frightend)
        {
            DisableScatteredLoop();
            qDebug() << "Choose Directions for Frightend mode";

            ChooseFrightendWay();
            m_movementDirection = ChooseShorterWay();
        }

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

void Red::GetAvialableDirections(double targetX, double targetY)
{
    m_availableDirections = {Directions::Left, Directions::Right, Directions::Down, Directions::Up};

    if(m_coordinates.x < targetX)
    {
        // left is blocked
        m_availableDirections.removeOne(Directions::Left);
    }

    if(m_coordinates.x > targetX)
    {
        // right is blocked
        m_availableDirections.removeOne(Directions::Right);
    }

    if(m_coordinates.y > targetY)
    {
        // down is blocked
        m_availableDirections.removeOne(Directions::Down);
    }

    if(m_coordinates.y < targetY)
    {
        // up is blocked
        m_availableDirections.removeOne(Directions::Up);
    }

    DeleteWayIfOnFrontBlock();
}

void Red::DeleteWayIfOnFrontBlock()
{
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
            if(int(m_coordinates.x) == 14 && int(m_coordinates.y) == 10)
            {
                m_availableDirections.removeOne(Directions::Right);
                count--;
                i--;
                continue;
            }
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
            if(int(m_coordinates.x) == 4 && int(m_coordinates.y) == 10)
            {
                m_availableDirections.removeOne(Directions::Left);
                count--;
                i--;
                continue;
            }
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
    setPos(pos().x(), pos().y() - DEFAULT_BLOCK_SIZE / 5);
    SetPositions();
    m_counter--;

    QPixmap pixmapItem(":/red/Images/Red/RedEnemyUp.png");
    pixmapItem = pixmapItem.scaled(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    setBrush(QBrush(pixmapItem));
}

void Red::MoveDown()
{
    setPos(pos().x(), pos().y() + DEFAULT_BLOCK_SIZE / 5);
    SetPositions();
    m_counter--;

    QPixmap pixmapItem(":/red/Images/Red/RedEnemyDown.png");
    pixmapItem = pixmapItem.scaled(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    setBrush(QBrush(pixmapItem));
}

void Red::MoveRight()
{
    setPos(pos().x() + DEFAULT_BLOCK_SIZE / 5, pos().y());
    SetPositions();
    m_counter--;

    QPixmap pixmapItem(":/red/Images/Red/RedEnemyRight.png");
    pixmapItem = pixmapItem.scaled(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    setBrush(QBrush(pixmapItem));
}

void Red::MoveLeft()
{
    setPos(pos().x() - DEFAULT_BLOCK_SIZE / 5, pos().y());
    SetPositions();
    m_counter--;

    QPixmap pixmapItem(":/red/Images/Red/RedEnemyLeft.png");
    pixmapItem = pixmapItem.scaled(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    setBrush(QBrush(pixmapItem));
}

// Scattered
Directions Red::ChooseScatteredShorterWay(double targetX, double targetY)
{
    if(m_availableDirections.size() == 1)
        return m_availableDirections.at(0);

    QMap<Directions, double> ways;

    for(int i = 0; i < m_availableDirections.size(); ++i)
    {
        if(m_availableDirections.at(i) == Directions::Up)
        {
            double x = std::abs(targetX - m_coordinates.x);
            double y = std::abs(targetY - (m_coordinates.y - 1));

            ways.insert(Directions::Up, sqrt(x * x + y * y));
        }
        if(m_availableDirections.at(i) == Directions::Down)
        {
            double x = std::abs(targetX - m_coordinates.x);
            double y = std::abs(targetY - (m_coordinates.y + 1));

            ways.insert(Directions::Down, sqrt(x * x + y * y));
        }
        if(m_availableDirections.at(i) == Directions::Right)
        {
            double x = std::abs(targetX - (m_coordinates.x + 1));
            double y = std::abs(targetY - m_coordinates.y);

            ways.insert(Directions::Right, sqrt(x * x + y * y));
        }
        if(m_availableDirections.at(i) == Directions::Left)
        {
            double x = std::abs(targetX - (m_coordinates.x - 1));
            double y = std::abs(targetY - m_coordinates.y);

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

void Red::ScatteredLoop()
{
    switch (m_scatteringStep)
    {
        case 0: m_movementDirection = Directions::Down; ++m_scatteringStep; break;
        case 1: m_movementDirection = Directions::Down; ++m_scatteringStep; break;
        case 2: m_movementDirection = Directions::Down; ++m_scatteringStep; break;

        case 3: m_movementDirection = Directions::Left; ++m_scatteringStep; break;
        case 4: m_movementDirection = Directions::Left; ++m_scatteringStep; break;
        case 5: m_movementDirection = Directions::Left; ++m_scatteringStep; break;

        case 6: m_movementDirection = Directions::Up; ++m_scatteringStep; break;
        case 7: m_movementDirection = Directions::Up; ++m_scatteringStep; break;
        case 8: m_movementDirection = Directions::Up; ++m_scatteringStep; break;

        case 9: m_movementDirection = Directions::Right; ++m_scatteringStep; break;
        case 10: m_movementDirection = Directions::Right; ++m_scatteringStep; break;
        default: m_scatteringStep = 0; break;
    }
}

void Red::DisableScatteredLoop()
{
    m_onScatteringLoop = false;
    m_scatteringStep = 0;
}

void Red::ChooseFrightendWay()
{
    m_availableDirections = {Directions::Left, Directions::Right, Directions::Down, Directions::Up};

    if(m_coordinates.x < CoreGlobals::playersCoords.x)
    {
        // Right is blocked
        m_availableDirections.removeOne(Directions::Right);
    }
    if(m_coordinates.x > CoreGlobals::playersCoords.x)
    {
        // Left is blocked
        m_availableDirections.removeOne(Directions::Left);
    }
    if(m_coordinates.y < CoreGlobals::playersCoords.y)
    {
        // Down is blocked
        m_availableDirections.removeOne(Directions::Down);
    }
    if(m_coordinates.y > CoreGlobals::playersCoords.y)
    {
        // left is blocked
        m_availableDirections.removeOne(Directions::Up);
    }

    DeleteWayIfOnFrontBlock();
}

void Red::ChangeStates()
{
    int x = m_state;
    x++;
    if(x == 3)
        x = 0;
    m_state = (GhostsStates)x;
}
