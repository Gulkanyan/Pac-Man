#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "Player.h"
#include "Red.h"
#include "Orange.h"
#include "Blue.h"
#include "Purple.h"

class Game : public QGraphicsView
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();

private:
    void keyPressEvent(QKeyEvent *event) override;

    void DrawMap(const std::vector<std::vector<int> > &vec);

    void fill(int x, int y);

    void InitInterface();

    void AddPlayer();

    void AddEnemies();

    void InitMovementTimer();

private slots:
    void DoMovement();
private:
    QGraphicsScene* scene;

    Player* m_player;
    Red * m_red;
};

#endif // GAME_H
