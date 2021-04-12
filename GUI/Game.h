#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "Player.h"
#include "Red.h"

class Game : public QGraphicsView
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();

    void keyPressEvent(QKeyEvent *event) override;
 //   void drawMap(const std::vector<std::vector<int> > &vec);
//    void fill(int x, int y);
private:
    QGraphicsScene* scene;

    Player* m_player;
    Red * m_red;
};

#endif // GAME_H
