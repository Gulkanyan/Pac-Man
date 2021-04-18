#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "Player.h"
#include "Red.h"
#include "Core/Orange.h"
#include "Core/Blue.h"
#include "Core/Purple.h"
#include "ShowPoint.h"

class Game : public QGraphicsView
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();
    void addToScene();

private:
    void keyPressEvent(QKeyEvent *event) override;

    void DrawMap(const std::vector<std::vector<int> > &vec);

    void fill(int x, int y);

    void fill_Coin(int x, int y);

    void fill_Pill(int x, int y);

    void InitInterface();

    void AddPlayer();

    void AddEnemies();

    void addScore();

    void InitMovementTimer();

private slots:
    void DoMovement();
private:
    QGraphicsScene* scene;

    Red * m_red;
    Orange * m_orange;
    Purple * m_purple;
    Blue * m_blue;

    Player * m_player;

    ShowPoint * m_showpoint;
};

#endif // GAME_H
