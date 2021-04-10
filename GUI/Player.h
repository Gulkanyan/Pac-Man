#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsRectItem>
#include<QKeyEvent>

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

private:
    void SetRightImage();
    void SetLeftImage();
    void SetUpImage();
    void SetDownImage();

private:
    Position m_state;
};

#endif // PLAYER_H
