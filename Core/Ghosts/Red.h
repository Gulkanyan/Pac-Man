#ifndef RED_H
#define RED_H

#include "Ghost.h"

class Red: public Ghost{
public:
    // constructors
    Red(Ghost* parent=NULL);

    void DoMove();

    void ChangeStates();

    void SetState(GhostsStates);

    void SetCounter(int);

private:
    void InitDefaultSettings();

    // Scattered mode
    void ScatteredLoop();
    void DisableScatteredLoop();

    void SetPositions();

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
