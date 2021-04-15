#ifndef COIN_H
#define COIN_H

#include <QGraphicsRectItem>

class Coin : public QObject, public QGraphicsRectItem
{
public:
    Coin(QGraphicsItem* parent = NULL);

    void SetPosition(int, int);
};

#endif // Coin_H
