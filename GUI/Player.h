#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsRectItem>

#include "Utils/Directions.h"

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

private:
    Step m_currentStep;
    int stepSize;
};

#endif // PLAYER_H
