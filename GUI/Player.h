#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsRectItem>

#include "CoreGlobals.h"

enum Step
{
    First,
    Second
};

class Player : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Player(QGraphicsItem* parent=NULL);

    void DoMovement();

    bool IsCollided(Directions);
    int GetStepSize();

    int GetScore();

private:
    void MoveRight();
    void MoveLeft();
    void MoveUp();
    void MoveDown();

    void SetRightImage();
    void SetLeftImage();
    void SetUpImage();
    void SetDownImage();
    void SetClosedRightImage();
    void SetClosedLeftImage();
    void SetClosedUpImage();
    void SetClosedDownImage();

signals:
    void ScoreIsUpdated(int);
    void PillIsEaten();
    void HealthIsUpdated(int);

private:
    Step m_currentStep;
    int stepSize;

    int m_score;
    int m_health;

public:
    bool m_IsMovementEnabled;
    Directions m_directions;
};

#endif // PLAYER_H
