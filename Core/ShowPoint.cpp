#include "ShowPoint.h"
#include <QFont>

ShowPoint::ShowPoint(QGraphicsTextItem *parent) :QGraphicsTextItem(parent)
{
    PaintShowPoint();
}

void ShowPoint::increaseShowPoint()
{
    showpoint += 50;
}

int ShowPoint::getShowPoint()
{
    return showpoint;
}
void ShowPoint::PaintShowPoint()
{
    setPlainText(QString("Միավոր: ")+ QString::number(showpoint));
    setDefaultTextColor(Qt::cyan);
    setFont(QFont("times",16));
}
