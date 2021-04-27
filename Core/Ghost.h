#ifndef GHOST_H
#define GHOST_H

#include <QGraphicsRectItem>

#include "CoreGlobals.h"

class Ghost : public QGraphicsRectItem{
public:
    // constructors
    Ghost(QGraphicsItem* parent=NULL);

protected:
    virtual void SetPositions();

    virtual QList<Directions> GetAvialableDirections(double targetX, double targetY, Coords selfCords);

    virtual QList<Directions> DeleteWayIfOnFrontBlock(QList<Directions> availableDirections, Coords selfCords);

    virtual Directions ChooseShorterWay(double targetX, double targetY, QList<Directions> availableDirections, Coords selfCords);

    virtual Directions ChooseFrightendWay(Coords selfCords);

    virtual Directions MoveToAvilablePoint(Coords selfCords);

    Directions GetShortestWay(double targetX, double targetY, Coords selfCords);

protected:
};

#endif // GHOST_H