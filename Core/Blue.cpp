#include "Blue.h"

#include <QBrush>

#include "Utils/Levels.h"
#include "CoreGlobals.h"

namespace
{
    Directions m_movementDirection = Directions::Unknown;
    bool m_onScatteringLoop = false;
    int m_scatteringStep = 0;
}

Blue::Blue(QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    InitDefaultSettings();
}

void Blue::InitDefaultSettings()
{
    setRect(0,0,DEFAULT_BLOCK_SIZE,DEFAULT_BLOCK_SIZE);
    QPixmap pixmapItem(":/blue/Images/Blue/BlueEnemyDown.png");
    pixmapItem = pixmapItem.scaled(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    setBrush(QBrush(pixmapItem));

    this->setPos(10 * DEFAULT_BLOCK_SIZE, 10 * DEFAULT_BLOCK_SIZE);

    SetPositions();

    m_state = GhostsStates::Chase;
    m_counter = 5;
}

void Blue::SetPositions()
{
    m_coordinates.x = this->pos().x() / DEFAULT_BLOCK_SIZE; // DEFAULT_BLOCK_SIZE means block size
    m_coordinates.y = this->pos().y() / DEFAULT_BLOCK_SIZE;
}

void Blue::DoMove()
{
    if(m_counter == 0)
    {
        if(m_state == GhostsStates::Chase)
        {
            DisableScatteBlueLoop();

            GetAvialableDirections(CoreGlobals::playersCoords.x, CoreGlobals::playersCoords.y);
            m_movementDirection = ChooseShorterWay();
        }
        else if(m_state == GhostsStates::Scattered)
        {
            qDebug() << "Scattered";
            if(m_coordinates.x == 1 && m_coordinates.y == 20)
                m_onScatteringLoop = true;

            if(m_onScatteringLoop)
                ScatteBlueLoop();
            else
            {
                GetAvialableDirections(1, 20);
                m_movementDirection = ChooseScatteBlueShorterWay(1, 20);
            }
        }
        else if(m_state == GhostsStates::Frightend)
        {
            DisableScatteBlueLoop();

            ChooseFrightendWay();
            m_movementDirection = ChooseShorterWay();
        }

        if(m_movementDirection == Directions::Unknown)
            m_movementDirection = MoveToAvilablePoint();

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

void Blue::GetAvialableDirections(double targetX, double targetY)
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

void Blue::DeleteWayIfOnFrontBlock()
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

Directions Blue::ChooseShorterWay()
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

void Blue::MoveUp()
{
    setPos(pos().x(), pos().y() - DEFAULT_BLOCK_SIZE / 5);
    SetPositions();
    m_counter--;

    QPixmap pixmapItem(":/blue/Images/Blue/BlueEnemyUp.png");
    pixmapItem = pixmapItem.scaled(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    setBrush(QBrush(pixmapItem));
}

void Blue::MoveDown()
{
    setPos(pos().x(), pos().y() + DEFAULT_BLOCK_SIZE / 5);
    SetPositions();
    m_counter--;

    QPixmap pixmapItem(":/blue/Images/Blue/BlueEnemyDown.png");
    pixmapItem = pixmapItem.scaled(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    setBrush(QBrush(pixmapItem));
}

void Blue::MoveRight()
{
    setPos(pos().x() + DEFAULT_BLOCK_SIZE / 5, pos().y());
    SetPositions();
    m_counter--;

    QPixmap pixmapItem(":/blue/Images/Blue/BlueEnemyRight.png");
    pixmapItem = pixmapItem.scaled(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    setBrush(QBrush(pixmapItem));
}

void Blue::MoveLeft()
{
    setPos(pos().x() - DEFAULT_BLOCK_SIZE / 5, pos().y());
    SetPositions();
    m_counter--;

    QPixmap pixmapItem(":/blue/Images/Blue/BlueEnemyLeft.png");
    pixmapItem = pixmapItem.scaled(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    setBrush(QBrush(pixmapItem));
}

// ScatteBlue
Directions Blue::ChooseScatteBlueShorterWay(double targetX, double targetY)
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

void Blue::ScatteBlueLoop()
{
    switch (m_scatteringStep)
    {
        case 0: m_movementDirection = Directions::Right; ++m_scatteringStep; break;
        case 1: m_movementDirection = Directions::Right; ++m_scatteringStep; break;
        case 2: m_movementDirection = Directions::Right; ++m_scatteringStep; break;
        case 3: m_movementDirection = Directions::Right; ++m_scatteringStep; break;
        case 4: m_movementDirection = Directions::Right; ++m_scatteringStep; break;
        case 5: m_movementDirection = Directions::Right; ++m_scatteringStep; break;
        case 6: m_movementDirection = Directions::Right; ++m_scatteringStep; break;

        case 7: m_movementDirection = Directions::Up; ++m_scatteringStep; break;
        case 8: m_movementDirection = Directions::Up; ++m_scatteringStep; break;

        case 9: m_movementDirection = Directions::Left; ++m_scatteringStep; break;
        case 10: m_movementDirection = Directions::Left; ++m_scatteringStep; break;

        case 11: m_movementDirection = Directions::Up; ++m_scatteringStep; break;
        case 12: m_movementDirection = Directions::Up; ++m_scatteringStep; break;

        case 13: m_movementDirection = Directions::Left; ++m_scatteringStep; break;
        case 14: m_movementDirection = Directions::Left; ++m_scatteringStep; break;

        case 15: m_movementDirection = Directions::Down; ++m_scatteringStep; break;
        case 16: m_movementDirection = Directions::Down; ++m_scatteringStep; break;

        case 17: m_movementDirection = Directions::Left; ++m_scatteringStep; break;
        case 18: m_movementDirection = Directions::Left; ++m_scatteringStep; break;
        case 19: m_movementDirection = Directions::Left; ++m_scatteringStep; break;

        case 20: m_movementDirection = Directions::Down; ++m_scatteringStep; break;

        default: m_scatteringStep = 0; break;
    }
}

void Blue::DisableScatteBlueLoop()
{
    m_onScatteringLoop = false;
    m_scatteringStep = 0;
}

void Blue::ChooseFrightendWay()
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

Directions Blue::MoveToAvilablePoint()
{
    QList<Directions> availableDirections = {Directions::Left, Directions::Right, Directions::Down, Directions::Up};

    // Delete way if front is block
    int count = availableDirections.size();
    for(int i = 0; i < count; ++i)
    {
        if(availableDirections.at(i) == Directions::Up)
        {
            if(Levels::level.at(m_coordinates.y - 1).at(m_coordinates.x) == 1)
            {
                availableDirections.removeOne(Directions::Up);
                count--;
                i--;
                continue;
            }
        }
        if(availableDirections.at(i) == Directions::Down)
        {
            if(Levels::level.at(m_coordinates.y + 1).at(m_coordinates.x) == 1)
            {
                availableDirections.removeOne(Directions::Down);
                count--;
                i--;
                continue;
            }
        }
        if(availableDirections.at(i) == Directions::Right)
        {
            if(int(m_coordinates.x) == 14 && int(m_coordinates.y) == 10)
            {
                availableDirections.removeOne(Directions::Right);
                count--;
                i--;
                continue;
            }
            if(Levels::level.at(m_coordinates.y).at(m_coordinates.x + 1) == 1)
            {
                availableDirections.removeOne(Directions::Right);
                count--;
                i--;
                continue;
            }
        }
        if(availableDirections.at(i) == Directions::Left)
        {
            if(int(m_coordinates.x) == 4 && int(m_coordinates.y) == 10)
            {
                availableDirections.removeOne(Directions::Left);
                count--;
                i--;
                continue;
            }
            if(Levels::level.at(m_coordinates.y).at(m_coordinates.x - 1) == 1)
            {
                availableDirections.removeOne(Directions::Left);
                count--;
                i--;
                continue;
            }
        }
    }

    int randVal = availableDirections.count();
    return availableDirections.at(rand() % randVal);
}

void Blue::ChangeStates()
{
    int x = m_state;
    x++;
    if(x == 3)
        x = 0;
    m_state = (GhostsStates)x;
}
