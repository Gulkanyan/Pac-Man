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

    void DeleteWayIfOnFrontBlock();

    // Chase mode
    Directions ChooseShorterWay();

    // Scattered
    Directions ChooseScatteredShorterWay(double targetX, double targetY);
    void ScatteredLoop();
    void DisableScatteredLoop();

    // Frightend
    void ChooseFrightendWay();

    void SetPositions();

    void MoveUp();
    void MoveDown();
    void MoveRight();
    void MoveLeft();

    Directions MoveToAvilablePoint();

private:

    Coords m_coordinates;
    QList<Directions> m_availableDirections;
    GhostsStates m_state;

public:
    int m_counter;
};

#endif
