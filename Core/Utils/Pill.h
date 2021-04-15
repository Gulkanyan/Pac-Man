#ifndef PILL_H
#define PILL_H

#include <QGraphicsRectItem>

class Pill : public QObject, public QGraphicsRectItem
{
public:
    Pill(QGraphicsItem* parent = NULL);

    void SetPosition(int, int);
};



#endif // PILL_H
