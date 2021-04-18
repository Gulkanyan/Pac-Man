#ifndef SHOWPOINT_H
#define SHOWPOINT_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QGraphicsTextItem>

class ShowPoint : public QGraphicsTextItem
{
public:
    explicit ShowPoint(QGraphicsTextItem *parent = nullptr);
    void increaseShowPoint();
    int getShowPoint();
    void PaintShowPoint();
private:
    int showpoint = 0;
};

#endif // SHOWPOINT_H
