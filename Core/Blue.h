#ifndef Blue_H
#define Blue_H

#include <QGraphicsRectItem>

#include "CoreGlobals.h"

class Blue: public QGraphicsRectItem{
public:
    // constructors
    Blue(QGraphicsItem* parent=NULL);

    void DoMove();

    void ChangeStates();

private:
    void InitDefaultSettings();

    void GetAvialableDirections(double targetX, double targetY);

    void DeleteWayIfOnFrontBlock();

    // Chase mode
    Directions ChooseShorterWay();

    // ScatteBlue
    Directions ChooseScatteBlueShorterWay(double targetX, double targetY);
    void ScatteBlueLoop();
    void DisableScatteBlueLoop();

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
