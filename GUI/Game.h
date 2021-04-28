#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>

#include "Player.h"
#include "Ghosts/Red.h"
#include "Ghosts/Orange.h"
#include "Ghosts/Blue.h"
#include "Ghosts/Purple.h"

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

    void InitPlayerTimer();

    void InitEnemysTimer();

    void NextLevel();

private slots:
    void DoMovement();

    void UpdateScore(int);
    void UpdateHealth(int);
    void GoToFrightenedMode();

    void DoEnemysMovement();

private:
    QGraphicsScene* scene;

    Red * m_red;
    Orange * m_orange;
    Purple * m_purple;
    Blue * m_blue;
    QGraphicsTextItem *m_scoreText;
    QGraphicsTextItem *m_healthText;



    Player * m_player;
};

#endif // GAME_H
