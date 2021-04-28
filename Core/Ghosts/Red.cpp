#include "Red.h"

#include <QBrush>

namespace
{
    Directions m_movementDirection = Directions::Unknown;
    Directions m_oldMoveDirection = Directions::Unknown;
    bool m_onScatteringLoop = false;
    int m_scatteringStep = 0;
    int m_frightenedCounter = 0;
}

Red::Red(Ghost *parent): Ghost(parent)
{
    InitDefaultSettings();
}

void Red::InitDefaultSettings()
{
    setRect(0,0,DEFAULT_BLOCK_SIZE,DEFAULT_BLOCK_SIZE);
    QPixmap pixmapItem(":/red/Images/Red/RedEnemyDown.png");
    pixmapItem = pixmapItem.scaled(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    setBrush(QBrush(pixmapItem));

    this->setPos(9 * DEFAULT_BLOCK_SIZE, 9 * DEFAULT_BLOCK_SIZE);

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
    if(m_counter == 0)
    {
        if(m_state == GhostsStates::Chase)
        {
            DisableScatteredLoop();

            m_movementDirection = GetShortestWay(CoreGlobals::playersCoords.x, CoreGlobals::playersCoords.y, m_coordinates);
        }
        else if(m_state == GhostsStates::Scattered)
        {
            if(m_coordinates.x == 17 && m_coordinates.y == 1)
                m_onScatteringLoop = true;

            if(m_onScatteringLoop)
                ScatteredLoop();
            else
            {
                m_movementDirection = GetShortestWay(17, 1, m_coordinates);
            }
        }
        else if(m_state == GhostsStates::Frightend)
        {
            DisableScatteredLoop();

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

    if(m_state == GhostsStates::Frightend)
    {
        QPixmap pixmapItem(":/images/Images/Frightened.png");
        pixmapItem = pixmapItem.scaled(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
        setBrush(QBrush(pixmapItem));
        m_oldMoveDirection = m_movementDirection;
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

void Red::MoveUp()
{
    setPos(pos().x(), pos().y() - DEFAULT_BLOCK_SIZE / 5);
    SetPositions();
    m_counter--;

    if(m_oldMoveDirection == m_movementDirection)
        return;

    QPixmap pixmapItem(":/red/Images/Red/RedEnemyUp.png");
    pixmapItem = pixmapItem.scaled(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    setBrush(QBrush(pixmapItem));
}

void Red::MoveDown()
{
    setPos(pos().x(), pos().y() + DEFAULT_BLOCK_SIZE / 5);
    SetPositions();
    m_counter--;

    if(m_oldMoveDirection == m_movementDirection)
        return;

    QPixmap pixmapItem(":/red/Images/Red/RedEnemyDown.png");
    pixmapItem = pixmapItem.scaled(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    setBrush(QBrush(pixmapItem));
}

void Red::MoveRight()
{
    setPos(pos().x() + DEFAULT_BLOCK_SIZE / 5, pos().y());
    SetPositions();
    m_counter--;

    if(m_oldMoveDirection == m_movementDirection)
        return;

    QPixmap pixmapItem(":/red/Images/Red/RedEnemyRight.png");
    pixmapItem = pixmapItem.scaled(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    setBrush(QBrush(pixmapItem));
}

void Red::MoveLeft()
{
    setPos(pos().x() - DEFAULT_BLOCK_SIZE / 5, pos().y());
    SetPositions();
    m_counter--;

    if(m_oldMoveDirection == m_movementDirection)
        return;

    QPixmap pixmapItem(":/red/Images/Red/RedEnemyLeft.png");
    pixmapItem = pixmapItem.scaled(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    setBrush(QBrush(pixmapItem));
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

void Red::ChangeStates()
{
    int x = m_state;
    x++;
    if(x == 3)
        x = 0;
    m_state = (GhostsStates)x;
}

void Red::SetState(GhostsStates state)
{
    m_state = state;
}

GhostsStates Red::GetState()
{
    return m_state;
}

void Red::SetCounter(int count)
{
    m_counter = count;
}

void Red::Reset()
{
    m_state = GhostsStates::Chase;
    m_movementDirection = Directions::Unknown;
    m_oldMoveDirection = Directions::Unknown;
    m_counter = 5;     //  start movement from first step
    setPos(9 * DEFAULT_BLOCK_SIZE, 9 * DEFAULT_BLOCK_SIZE);
}
