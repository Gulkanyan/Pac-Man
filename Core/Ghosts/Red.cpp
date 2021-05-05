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

    this->setPos(9 * DEFAULT_BLOCK_SIZE, 9 * DEFAULT_BLOCK_SIZE);

    SetPositions();

    m_movementDirection = Directions::Unknown;
    m_state = GhostsStates::Chase;
    m_counter = 5;

    QPixmap pixmapItem(GetPixmapStringForMultiplayer(m_movementDirection));

    pixmapItem = pixmapItem.scaled(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    setBrush(QBrush(pixmapItem));
}

void Red::SetPositions()
{
    m_coordinates.x = this->pos().x() / DEFAULT_BLOCK_SIZE; // DEFAULT_BLOCK_SIZE means block size
    m_coordinates.y = this->pos().y() / DEFAULT_BLOCK_SIZE;
}

void Red::DoMove(Directions manualMovementDirection)
{
    if(CoreGlobals::multiplayerSettings.isEnabled == true)
    {
        if(m_counter == 0)
        {
            if(IsDirectionValid(m_coordinates, manualMovementDirection))
            {
                m_movementDirection = manualMovementDirection;
            }
            if(IsDirectionValid(m_coordinates, m_movementDirection) == false)
            {
                m_movementDirection = Directions::Unknown;
            }

            m_counter = 5;
        }
    }
    else
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

void Red::MoveUp()
{
    setPos(pos().x(), pos().y() - DEFAULT_BLOCK_SIZE / 5);
    SetPositions();
    m_counter--;

    if(m_oldMoveDirection == m_movementDirection)
        return;

    QPixmap pixmapItem(GetPixmapStringForMultiplayer(m_movementDirection));
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

    QPixmap pixmapItem(GetPixmapStringForMultiplayer(m_movementDirection));
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

    QPixmap pixmapItem(GetPixmapStringForMultiplayer(m_movementDirection));
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

    QPixmap pixmapItem(GetPixmapStringForMultiplayer(m_movementDirection));
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
    m_frightenedCounter = 0;
    setPos(9 * DEFAULT_BLOCK_SIZE, 9 * DEFAULT_BLOCK_SIZE);
}

void Red::ResetMovementDirection()
{
    m_movementDirection = Directions::Unknown;
    m_oldMoveDirection = Directions::Down;
}

QString Red::GetPixmapStringForMultiplayer(Directions dir)
{
    QString pixmapItemPath = ":/red/Images/Red/RedEnemyDown.png";

    if(CoreGlobals::multiplayerSettings.isEnabled)
    {
        switch (CoreGlobals::multiplayerSettings.selectedGhost)
        {
            case Ghosts::Red_Ghost :
                switch (dir)
                {
                    case Directions::Up : pixmapItemPath = ":/red/Images/Red/RedEnemyUp.png"; break;
                    case Directions::Down : pixmapItemPath = ":/red/Images/Red/RedEnemyDown.png"; break;
                    case Directions::Left : pixmapItemPath = ":/red/Images/Red/RedEnemyLeft.png"; break;
                    case Directions::Right : pixmapItemPath = ":/red/Images/Red/RedEnemyRight.png"; break;
                    default : pixmapItemPath = ":/red/Images/Red/RedEnemyDown.png"; break;
                }
            break;

            case Ghosts::Blue_Ghost :
                switch (dir)
                {
                    case Directions::Up : pixmapItemPath = ":/blue/Images/Blue/BlueEnemyUp.png"; break;
                    case Directions::Down : pixmapItemPath = ":/blue/Images/Blue/BlueEnemyDown.png"; break;
                    case Directions::Left : pixmapItemPath = ":/blue/Images/Blue/BlueEnemyLeft.png"; break;
                    case Directions::Right : pixmapItemPath = ":/blue/Images/Blue/BlueEnemyRight.png"; break;
                    default : pixmapItemPath = ":/blue/Images/Blue/BlueEnemyDown.png"; break;
                }
            break;
            case Ghosts::Orange_Ghost :
                switch (dir)
                {
                    case Directions::Up : pixmapItemPath = ":/Orange/Images/Orange/OrangeEnemyUp.png"; break;
                    case Directions::Down : pixmapItemPath = ":/Orange/Images/Orange/OrangeEnemyDown.png"; break;
                    case Directions::Left : pixmapItemPath = ":/Orange/Images/Orange/OrangeEnemyLeft.png"; break;
                    case Directions::Right : pixmapItemPath = ":/Orange/Images/Orange/OrangeEnemyRight.png"; break;
                    default : pixmapItemPath = ":/Orange/Images/Orange/OrangeEnemyDown.png"; break;
                }
            break;
            case Ghosts::Purple_Ghost :
                switch (dir)
                {
                    case Directions::Up : pixmapItemPath = ":/Purple/Images/Purple/PurpleEnemyUp.png"; break;
                    case Directions::Down : pixmapItemPath = ":/Purple/Images/Purple/PurpleEnemyDown.png"; break;
                    case Directions::Left : pixmapItemPath = ":/Purple/Images/Purple/PurpleEnemyLeft.png"; break;
                    case Directions::Right : pixmapItemPath = ":/Purple/Images/Purple/PurpleEnemyRight.png"; break;
                    default : pixmapItemPath = ":/Purple/Images/Purple/PurpleEnemyDown.png"; break;
                }
            break;
            default : pixmapItemPath = ":/red/Images/Red/RedEnemyDown.png"; break;
        }
    }
    else
    {
        switch (dir)
        {
            case Directions::Up : pixmapItemPath = ":/red/Images/Red/RedEnemyUp.png"; break;
            case Directions::Down : pixmapItemPath = ":/red/Images/Red/RedEnemyDown.png"; break;
            case Directions::Left : pixmapItemPath = ":/red/Images/Red/RedEnemyLeft.png"; break;
            case Directions::Right : pixmapItemPath = ":/red/Images/Red/RedEnemyRight.png"; break;
            default : pixmapItemPath = ":/red/Images/Red/RedEnemyDown.png"; break;
        }
    }

    return pixmapItemPath;
}
