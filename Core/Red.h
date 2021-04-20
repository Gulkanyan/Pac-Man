#ifndef RED_H
#define RED_H

#include <QGraphicsRectItem>

#include "CoreGlobals.h"

class Red: public QGraphicsRectItem{
public:
    // constructors
    Red(QGraphicsItem* parent=NULL);

    void DoMove();

    void ChangeStates();

private:
    void InitDefaultSettings();

    void GetAvialableDirections(double targetX, double targetY);

    // Chase mode
    Directions ChooseShorterWay();

    // Scattered
    Directions ChooseScatteredShorterWay(double targetX, double targetY);

    void SetPositions();

    void MoveUp();
    void MoveDown();
    void MoveRight();
    void MoveLeft();

private:

    Coords m_coordinates;
    QList<Directions> m_availableDirections;
    GhostsStates m_state;
};

#endif
