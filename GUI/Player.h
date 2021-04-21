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

    void MoveRight();
    void MoveLeft();
    void MoveUp();
    void MoveDown();
    bool IsCollided(Directions);
    int GetStepSize();

private:
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
    void HealthIsUpdated(int);

private:
    Step m_currentStep;
    int stepSize;

    int m_score;
    int m_health;
};

#endif // PLAYER_H
