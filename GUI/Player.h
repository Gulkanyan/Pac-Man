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
    Step m_currentStep;
};

#endif // PLAYER_H
