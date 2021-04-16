#ifndef PURPLE_H
#define PURPLE_H

#include <QGraphicsRectItem>
#include <QPainter>
#include <QPaintEvent>
#include <QMainWindow>
#include <QObject>

class Purple: public QGraphicsRectItem{
public:
    // constructors
    Purple(QGraphicsItem* parent=NULL);

};

#endif
