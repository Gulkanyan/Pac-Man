#ifndef GHOST_H
#define GHOST_H

#include <QGraphicsRectItem>

#include "CoreGlobals.h"

class Ghost : public QGraphicsRectItem{
public:
    // constructors
    Ghost(QGraphicsItem* parent=NULL);

protected:
    virtual QList<Directions> GetAvialableDirections(double targetX, double targetY, Coords selfCords);

    virtual QList<Directions> DeleteWayIfOnFrontBlock(QList<Directions> availableDirections, Coords selfCords);

    virtual Directions ChooseShorterWay(double targetX, double targetY, QList<Directions> availableDirections, Coords selfCords);

    virtual Directions ChooseFrightendWay(Coords selfCords);

    virtual Directions MoveToAvilablePoint(Coords selfCords);

    virtual bool IsDirectionValid(Coords selfCords, Directions movementDirection);

    Directions GetShortestWay(double targetX, double targetY, Coords selfCords);
    Directions GetShortestWayForPurple(double targetX, double targetY, Coords selfCords);

protected:
};

#endif // GHOST_H
