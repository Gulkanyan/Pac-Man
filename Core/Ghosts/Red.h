#ifndef RED_H
#define RED_H

#include <QGraphicsRectItem>

#include "CoreGlobals.h"
#include "Ghost.h"

class Red: public Ghost{
public:
    // constructors
    Red(Ghost* parent=NULL);

    void DoMove();

    void ChangeStates();

private:
    void InitDefaultSettings();

    // Scattered mode
    void ScatteredLoop();
    void DisableScatteredLoop();

    void SetPositions() override;

    void MoveUp();
    void MoveDown();
    void MoveRight();
    void MoveLeft();

private:

    Coords m_coordinates;
    QList<Directions> m_availableDirections;
    GhostsStates m_state;

public:
    int m_counter;
};

#endif