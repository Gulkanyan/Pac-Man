#include "Purple.h"
#include <QBrush>

namespace
{
    Directions m_movementDirection = Directions::Unknown;
    bool m_onScatteringLoop = false;
    int m_scatteringStep = 0;
}

Purple::Purple(Ghost *parent): Ghost(parent)
{
    InitDefaultSettings();
}

void Purple::InitDefaultSettings()
{
    setRect(0,0,DEFAULT_BLOCK_SIZE,DEFAULT_BLOCK_SIZE);
    QPixmap pixmapItem(":/Purple/Images/Purple/PurpleEnemyDown.png");
    pixmapItem = pixmapItem.scaled(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    setBrush(QBrush(pixmapItem));

    this->setPos(10 * DEFAULT_BLOCK_SIZE, 9 * DEFAULT_BLOCK_SIZE);

    SetPositions();

    m_state = GhostsStates::Chase;
    m_counter = 5;
}

void Purple::SetPositions()
{
    m_coordinates.x = this->pos().x() / DEFAULT_BLOCK_SIZE; // DEFAULT_BLOCK_SIZE means block size
    m_coordinates.y = this->pos().y() / DEFAULT_BLOCK_SIZE;
}

void Purple::DoMove(Directions targetDirection)
{
    if(m_counter == 0)
    {
        if(m_state == GhostsStates::Chase)
        {
            DisableScatteBlueLoop();

            Coords targetCords;
            ChooseFrontPointOfTarget(targetDirection, targetCords);

            m_movementDirection = GetShortestWayForPurple(targetCords.x, targetCords.y, m_coordinates);
        }
        else if(m_state == GhostsStates::Scattered)
        {
            if(m_coordinates.x == 1 && m_coordinates.y == 1)
                m_onScatteringLoop = true;

            if(m_onScatteringLoop)
                ScatteringLoop();
            else
            {
                m_movementDirection = GetShortestWay(1, 1, m_coordinates);
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

    switch (m_movementDirection)
    {
        case Directions::Up: MoveUp(); break;

        case Directions::Down: MoveDown(); break;

        case Directions::Right: MoveRight(); break;

        case Directions::Left: MoveLeft(); break;

        default: qDebug() << "Direction is uncnown"; m_counter--; break;
    }
}

void Purple::MoveUp()
{
    setPos(pos().x(), pos().y() - DEFAULT_BLOCK_SIZE / 5);
    SetPositions();
    m_counter--;

    QPixmap pixmapItem(":/Purple/Images/Purple/PurpleEnemyUp.png");
    pixmapItem = pixmapItem.scaled(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    setBrush(QBrush(pixmapItem));
}

void Purple::MoveDown()
{
    setPos(pos().x(), pos().y() + DEFAULT_BLOCK_SIZE / 5);
    SetPositions();
    m_counter--;

    QPixmap pixmapItem(":/Purple/Images/Purple/PurpleEnemyDown.png");
    pixmapItem = pixmapItem.scaled(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    setBrush(QBrush(pixmapItem));
}

void Purple::MoveRight()
{
    setPos(pos().x() + DEFAULT_BLOCK_SIZE / 5, pos().y());
    SetPositions();
    m_counter--;

    QPixmap pixmapItem(":/Purple/Images/Purple/PurpleEnemyRight.png");
    pixmapItem = pixmapItem.scaled(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    setBrush(QBrush(pixmapItem));
}

void Purple::MoveLeft()
{
    setPos(pos().x() - DEFAULT_BLOCK_SIZE / 5, pos().y());
    SetPositions();
    m_counter--;

    QPixmap pixmapItem(":/Purple/Images/Purple/PurpleEnemyLeft.png");
    pixmapItem = pixmapItem.scaled(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    setBrush(QBrush(pixmapItem));
}

// Scattered mode
void Purple::ScatteringLoop()
{
    switch (m_scatteringStep)
    {
        case 0: m_movementDirection = Directions::Down; ++m_scatteringStep; break;
        case 1: m_movementDirection = Directions::Down; ++m_scatteringStep; break;
        case 2: m_movementDirection = Directions::Down; ++m_scatteringStep; break;

        case 3: m_movementDirection = Directions::Right; ++m_scatteringStep; break;
        case 4: m_movementDirection = Directions::Right; ++m_scatteringStep; break;
        case 5: m_movementDirection = Directions::Right; ++m_scatteringStep; break;

        case 6: m_movementDirection = Directions::Up; ++m_scatteringStep; break;
        case 7: m_movementDirection = Directions::Up; ++m_scatteringStep; break;
        case 8: m_movementDirection = Directions::Up; ++m_scatteringStep; break;

        case 9: m_movementDirection = Directions::Left; ++m_scatteringStep; break;
        case 10: m_movementDirection = Directions::Left; ++m_scatteringStep; break;
        default: m_scatteringStep = 0; break;
    }
}

void Purple::ChooseFrontPointOfTarget(Directions targetDirection, Coords &targetCoords)
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

void Purple::DisableScatteBlueLoop()
{
    m_onScatteringLoop = false;
    m_scatteringStep = 0;
}

void Purple::ChangeStates()
{
    int x = m_state;
    x++;
    if(x == 3)
        x = 0;
    m_state = (GhostsStates)x;
}

void Purple::SetState(GhostsStates state)
{
    m_state = state;
}

void Purple::SetCounter(int count)
{
    m_counter = count;
}
