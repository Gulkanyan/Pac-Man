#ifndef ORANGE_H
#define ORANGE_H

#include <QPainter>
#include <QPaintEvent>
#include <QMainWindow>
#include <QObject>

#include "Ghost.h"

class Orange: public Ghost{
public:
    // constructors
    Orange(Ghost* parent=NULL);

};

#endif
