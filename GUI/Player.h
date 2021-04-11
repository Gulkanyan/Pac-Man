#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsRectItem>
#include<QKeyEvent>

enum Step
{
    First,
    Second
};

enum Position
{
    Left,
    Right,
    Up,
    Down
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

public:
    void SetRightImage();
    void SetLeftImage();
    void SetUpImage();
    void SetDownImage();

    void SetClosedRightImage();

private:
    Position m_state;

    Step m_currentStep;
};

#endif // PLAYER_H
