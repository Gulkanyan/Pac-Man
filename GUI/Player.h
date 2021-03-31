#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsRectItem>

class Player : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Player(QGraphicsItem* parent=NULL);
};

#endif // PLAYER_H
