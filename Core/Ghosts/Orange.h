#ifndef ORANGE_H
#define ORANGE_H

#include "Ghost.h"

class Orange: public Ghost{
public:
    // constructors
    Orange(Ghost* parent=NULL);

    void DoMove(Directions targetDirection);

    void ChangeStates();

private:
    void InitDefaultSettings();

    // ScatteBlue
    void ScatteringLoop();
    void DisableScatteBlueLoop();

    void SetPositions() override;

    void MoveUp();
    void MoveDown();
    void MoveRight();
    void MoveLeft();

    void ChooseBottomPointOfTarget(Directions targetDirection, Coords &targetCoords);

private:

    Coords m_coordinates;
    QList<Directions> m_availableDirections;
    GhostsStates m_state;

public:
    int m_counter;
};

#endif
