#include "Ghost.h"

#include <QGraphicsItem>

Ghost::Ghost(QGraphicsItem *parent): QGraphicsRectItem(parent)
{

}


Directions Ghost::GetShortestWay(double targetX, double targetY, Coords selfCords)
{
    QList<Directions> availableDirections = GetAvialableDirections(targetX, targetY, selfCords);
    availableDirections = DeleteWayIfOnFrontBlock(availableDirections, selfCords);
    return ChooseShorterWay(targetX, targetY, availableDirections, selfCords);
}

Directions Ghost::GetShortestWayForPurple(double targetX, double targetY, Coords selfCords)
{
    QList<Directions> availableDirections;

    if(abs((int)(targetX + targetY) - (int)(selfCords.x + selfCords.y)) <= 5)
        availableDirections = GetAvialableDirections(targetX, targetY, selfCords);
    else
        return MoveToAvilablePoint(selfCords);

    availableDirections = DeleteWayIfOnFrontBlock(availableDirections, selfCords);
    return ChooseShorterWay(targetX, targetY, availableDirections, selfCords);
}

QList<Directions> Ghost::GetAvialableDirections(double targetX, double targetY, Coords selfCords)
{
    QList<Directions> availableDirections = {Directions::Left, Directions::Right, Directions::Down, Directions::Up};

    if(selfCords.x < targetX)
    {
        // left is blocked
        availableDirections.removeOne(Directions::Left);
    }

    if(selfCords.x > targetX)
    {
        // right is blocked
        availableDirections.removeOne(Directions::Right);
    }

    if(selfCords.y > targetY)
    {
        // down is blocked
        availableDirections.removeOne(Directions::Down);
    }

    if(selfCords.y < targetY)
    {
        // up is blocked
        availableDirections.removeOne(Directions::Up);
    }

    return availableDirections;
}

QList<Directions> Ghost::DeleteWayIfOnFrontBlock(QList<Directions> availableDirections, Coords selfCords)
{
    // Delete way if front is block
    int count = availableDirections.size();
    for(int i = 0; i < count; ++i)
    {
        if(availableDirections.at(i) == Directions::Up)
        {
            if(Levels::level.at(selfCords.y - 1).at(selfCords.x) == 1)
            {
                availableDirections.removeOne(Directions::Up);
                count--;
                i--;
                continue;
            }
        }
        if(availableDirections.at(i) == Directions::Down)
        {
            if(Levels::level.at(selfCords.y + 1).at(selfCords.x) == 1)
            {
                availableDirections.removeOne(Directions::Down);
                count--;
                i--;
                continue;
            }
        }
        if(availableDirections.at(i) == Directions::Right)
        {
            if(int(selfCords.x) == 14 && int(selfCords.y) == 10)
            {
                availableDirections.removeOne(Directions::Right);
                count--;
                i--;
                continue;
            }
            if(Levels::level.at(selfCords.y).at(selfCords.x + 1) == 1)
            {
                availableDirections.removeOne(Directions::Right);
                count--;
                i--;
                continue;
            }
        }
        if(availableDirections.at(i) == Directions::Left)
        {
            if(int(selfCords.x) == 4 && int(selfCords.y) == 10)
            {
                availableDirections.removeOne(Directions::Left);
                count--;
                i--;
                continue;
            }
            if(Levels::level.at(selfCords.y).at(selfCords.x - 1) == 1)
            {
                availableDirections.removeOne(Directions::Left);
                count--;
                i--;
                continue;
            }
        }
    }
    return availableDirections;
}

Directions Ghost::ChooseShorterWay(double targetX, double targetY, QList<Directions> availableDirections, Coords selfCords)
{
    if(availableDirections.size() == 1)
        return availableDirections.at(0);

    QMap<Directions, double> ways;

    for(int i = 0; i < availableDirections.size(); ++i)
    {
        if(availableDirections.at(i) == Directions::Up)
        {
            double x = std::abs(targetX - selfCords.x);
            double y = std::abs(targetY - (selfCords.y - 1));

            ways.insert(Directions::Up, sqrt(x * x + y * y));
        }
        if(availableDirections.at(i) == Directions::Down)
        {
            double x = std::abs(targetX - selfCords.x);
            double y = std::abs(targetY - (selfCords.y + 1));

            ways.insert(Directions::Down, sqrt(x * x + y * y));
        }
        if(availableDirections.at(i) == Directions::Right)
        {
            double x = std::abs(targetX - (selfCords.x + 1));
            double y = std::abs(targetY - selfCords.y);

            ways.insert(Directions::Right, sqrt(x * x + y * y));
        }
        if(availableDirections.at(i) == Directions::Left)
        {
            double x = std::abs(targetX - (selfCords.x - 1));
            double y = std::abs(targetY - selfCords.y);

            ways.insert(Directions::Left, sqrt(x * x + y * y));
        }
    }

    Directions movementDirection = Directions::Unknown;
    if((int)availableDirections.size() == 3)
    {
        if(ways.value(availableDirections.at(0)) < ways.value(availableDirections.at(1)))
        {
            if(ways.value(availableDirections.at(0)) < ways.value(availableDirections.at(2)))
            {
                movementDirection = availableDirections.at(0);
            }
            else
            {
                movementDirection = availableDirections.at(2);
            }
        }
        else if(ways.value(availableDirections.at(1)) < ways.value(availableDirections.at(2)))
        {
            movementDirection = availableDirections.at(1);
        }
        else
        {
            movementDirection = availableDirections.at(2);
        }
    }
    else if(availableDirections.size() == 2)
    {
        if(ways.value(availableDirections.at(0)) < ways.value(availableDirections.at(1)))
        {
            movementDirection = availableDirections.at(0);
        }
        else
        {
            movementDirection = availableDirections.at(1);
        }
    }

    return movementDirection;
}

Directions Ghost::ChooseFrightendWay(Coords selfCords)
{
    QList<Directions> availableDirections = {Directions::Left, Directions::Right, Directions::Down, Directions::Up};

    if(selfCords.x < CoreGlobals::playersCoords.x)
    {
        // Right is blocked
        availableDirections.removeOne(Directions::Right);
    }
    if(selfCords.x > CoreGlobals::playersCoords.x)
    {
        // Left is blocked
        availableDirections.removeOne(Directions::Left);
    }
    if(selfCords.y < CoreGlobals::playersCoords.y)
    {
        // Down is blocked
        availableDirections.removeOne(Directions::Down);
    }
    if(selfCords.y > CoreGlobals::playersCoords.y)
    {
        // left is blocked
        availableDirections.removeOne(Directions::Up);
    }

    availableDirections = DeleteWayIfOnFrontBlock(availableDirections, selfCords);
    return ChooseShorterWay(CoreGlobals::playersCoords.x, CoreGlobals::playersCoords.y, availableDirections, selfCords);
}

Directions Ghost::MoveToAvilablePoint(Coords selfCords)
{
    QList<Directions> availableDirections = {Directions::Left, Directions::Right, Directions::Down, Directions::Up};

    // Delete way if front is block
    int count = availableDirections.size();
    for(int i = 0; i < count; ++i)
    {
        if(availableDirections.at(i) == Directions::Up)
        {
            if(Levels::level.at(selfCords.y - 1).at(selfCords.x) == 1)
            {
                availableDirections.removeOne(Directions::Up);
                count--;
                i--;
                continue;
            }
        }
        if(availableDirections.at(i) == Directions::Down)
        {
            if(Levels::level.at(selfCords.y + 1).at(selfCords.x) == 1)
            {
                availableDirections.removeOne(Directions::Down);
                count--;
                i--;
                continue;
            }
        }
        if(availableDirections.at(i) == Directions::Right)
        {
            if(int(selfCords.x) == 14 && int(selfCords.y) == 10)
            {
                availableDirections.removeOne(Directions::Right);
                count--;
                i--;
                continue;
            }
            if(Levels::level.at(selfCords.y).at(selfCords.x + 1) == 1)
            {
                availableDirections.removeOne(Directions::Right);
                count--;
                i--;
                continue;
            }
        }
        if(availableDirections.at(i) == Directions::Left)
        {
            if(int(selfCords.x) == 4 && int(selfCords.y) == 10)
            {
                availableDirections.removeOne(Directions::Left);
                count--;
                i--;
                continue;
            }
            if(Levels::level.at(selfCords.y).at(selfCords.x - 1) == 1)
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
