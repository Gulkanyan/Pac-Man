#ifndef ORANGE_H
#define ORANGE_H

#include <QGraphicsRectItem>
#include <QPainter>
#include <QPaintEvent>
#include <QMainWindow>
#include <QObject>

class Orange: public QGraphicsRectItem{
public:
    // constructors
    Orange(QGraphicsItem* parent=NULL);

};

#endif
