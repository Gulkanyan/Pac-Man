#ifndef PURPLE_H
#define PURPLE_H

#include "Ghost.h"

class Purple: public Ghost
{
public:
    // constructors
    Purple(Ghost* parent=NULL);

    void DoMove(Directions targetDirection);

    void ChangeStates();

    void SetState(GhostsStates);
    GhostsStates GetState();

    void SetCounter(int);

    void Reset();

private:
    void InitDefaultSettings();

    // ScatteBlue
    void ScatteringLoop();
    void DisableScatteBlueLoop();

    void SetPositions();

    void MoveUp();
    void MoveDown();
    void MoveRight();
    void MoveLeft();

    void ChooseFrontPointOfTarget(Directions targetDirection, Coords &targetCoords);

private:

    Coords m_coordinates;
    QList<Directions> m_availableDirections;
    GhostsStates m_state;

public:
    int m_counter;
};

#endif
