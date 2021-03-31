#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>


class Game : public QGraphicsView
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();

    QGraphicsScene* scene;
};

#endif // GAME_H
