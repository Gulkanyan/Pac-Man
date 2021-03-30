#ifndef PLAYER_H
#define PLAYER_H

#include <QMainWindow>
#include <QGraphicsEllipseItem>

class Player : public QObject, public QGraphicsEllipseItem
{

    Q_OBJECT

public:
    explicit Player(QWidget *parent = nullptr);
    ~Player();

private:
};

#endif // PLAYER_H
