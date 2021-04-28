#include "Blue.h"

#include <QBrush>

namespace
{
    Directions m_movementDirection = Directions::Unknown;
    Directions m_oldMoveDirection = Directions::Unknown;
    bool m_onScatteringLoop = false;
    int m_scatteringStep = 0;
    int m_frightenedCounter = 0;
}

Blue::Blue(Ghost *parent): Ghost(parent)
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

void Blue::DoMove(Directions targetDirection)
{
    if(m_counter == 0)
    {
        if(m_state == GhostsStates::Chase)
        {
            DisableScatteBlueLoop();

            Coords targetCords;
            ChooseFrontPointOfTarget(targetDirection, targetCords);

            m_movementDirection = GetShortestWay(targetCords.x, targetCords.y, m_coordinates);
        }
        else if(m_state == GhostsStates::Scattered)
        {
            if(m_coordinates.x == 1 && m_coordinates.y == 20)
                m_onScatteringLoop = true;

            if(m_onScatteringLoop)
                ScatteringLoop();
            else
            {
                m_movementDirection = GetShortestWay(1, 20, m_coordinates);
            }
        }
        else if(m_state == GhostsStates::Frightend)
        {
            DisableScatteBlueLoop();

            m_movementDirection = ChooseFrightendWay(m_coordinates);
        }

        if(m_movementDirection == Directions::Unknown)
            m_movementDirection = MoveToAvilablePoint(m_coordinates);

        m_counter = 5;
    }

    if(m_frightenedCounter == FRIGHTENED_MODE_STEPS)
    {
        m_state = GhostsStates::Chase;
        m_frightenedCounter = 0;
    }

    if(m_state == GhostsStates::Frightend || m_state == GhostsStates::Scattered)
    {
        if(m_state == GhostsStates::Frightend)
        {
            QPixmap pixmapItem(":/images/Images/Frightened.png");
            pixmapItem = pixmapItem.scaled(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
            setBrush(QBrush(pixmapItem));
            m_oldMoveDirection = m_movementDirection;
        }
        m_frightenedCounter++;
    }

    switch (m_movementDirection)
    {
        case Directions::Up: MoveUp(); break;

        case Directions::Down: MoveDown(); break;

        case Directions::Right: MoveRight(); break;

        case Directions::Left: MoveLeft(); break;

        default: qDebug() << "Direction is uncnown"; m_counter--; break;
    }
    m_oldMoveDirection = m_movementDirection;
}

void Blue::MoveUp()
{
    setPos(pos().x(), pos().y() - DEFAULT_BLOCK_SIZE / 5);
    SetPositions();
    m_counter--;

    if(m_oldMoveDirection == m_movementDirection)
        return;

    QPixmap pixmapItem(":/blue/Images/Blue/BlueEnemyUp.png");
    pixmapItem = pixmapItem.scaled(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    setBrush(QBrush(pixmapItem));
}

void Blue::MoveDown()
{
    setPos(pos().x(), pos().y() + DEFAULT_BLOCK_SIZE / 5);
    SetPositions();
    m_counter--;

    if(m_oldMoveDirection == m_movementDirection)
        return;

    QPixmap pixmapItem(":/blue/Images/Blue/BlueEnemyDown.png");
    pixmapItem = pixmapItem.scaled(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    setBrush(QBrush(pixmapItem));
}

void Blue::MoveRight()
{
    setPos(pos().x() + DEFAULT_BLOCK_SIZE / 5, pos().y());
    SetPositions();
    m_counter--;

    if(m_oldMoveDirection == m_movementDirection)
        return;

    QPixmap pixmapItem(":/blue/Images/Blue/BlueEnemyRight.png");
    pixmapItem = pixmapItem.scaled(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    setBrush(QBrush(pixmapItem));
}

void Blue::MoveLeft()
{
    setPos(pos().x() - DEFAULT_BLOCK_SIZE / 5, pos().y());
    SetPositions();
    m_counter--;

    if(m_oldMoveDirection == m_movementDirection)
        return;

    QPixmap pixmapItem(":/blue/Images/Blue/BlueEnemyLeft.png");
    pixmapItem = pixmapItem.scaled(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    setBrush(QBrush(pixmapItem));
}

// Scattered mode
void Blue::ScatteringLoop()
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

void Blue::ChooseFrontPointOfTarget(Directions targetDirection, Coords &targetCoords)
{
    targetCoords = CoreGlobals::playersCoords;

    if(targetDirection == Directions::Up)
    {
        targetCoords.y = targetCoords.y - 1;
        return;
    }
    else if(targetDirection == Directions::Down)
    {
        targetCoords.y = targetCoords.y + 1;
        return;
    }
    else if(targetDirection == Directions::Right)
    {
        targetCoords.x = targetCoords.x + 1;
        return;
    }
    else if(targetDirection == Directions::Left)
    {
        targetCoords.x = targetCoords.x - 1;
        return;
    }
}

void Blue::DisableScatteBlueLoop()
{
    m_onScatteringLoop = false;
    m_scatteringStep = 0;
}

void Blue::ChangeStates()
{
    int x = m_state;
    x++;
    if(x == 3)
        x = 0;
    m_state = (GhostsStates)x;
}

void Blue::SetState(GhostsStates state)
{
    m_state = state;
}

GhostsStates Blue::GetState()
{
    return m_state;
}

void Blue::SetCounter(int count)
{
    m_counter = count;
}

void Blue::Reset()
{
    m_state = GhostsStates::Chase;
    m_movementDirection = Directions::Unknown;
    m_oldMoveDirection = Directions::Unknown;
    m_counter = 5;     //  start movement from first step
    m_frightenedCounter = 0;
    setPos(10 * DEFAULT_BLOCK_SIZE, 10 * DEFAULT_BLOCK_SIZE);
}
