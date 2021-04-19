#ifndef RED_H
#define RED_H

#include <QGraphicsRectItem>

#include "CoreGlobals.h"

class Red: public QGraphicsRectItem{
public:
    // constructors
    Red(QGraphicsItem* parent=NULL);

    void DoMove();

private:
    void InitDefaultSettings();

    void GetAvilableDirections();

    Directions ChooseShorterWay();

    void SetPositions();

private:

    Coords m_coordinates;
    QList<Directions> m_availableDirections;
};

#endif
