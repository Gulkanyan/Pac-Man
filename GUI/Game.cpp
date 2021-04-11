#include "Game.h"
#include "ui_Game.h"

Game::Game(QWidget *parent) :
    QGraphicsView(parent),
    scene(new QGraphicsScene(this))
{
    scene = new QGraphicsScene(0,0,790,790);
    setScene(scene);
    setFixedSize(800,800);
    setStyleSheet("background-color:black;");
    setAutoFillBackground( true );

    m_player = new Player();
    m_player->setPos(50,350);
    scene->addItem(m_player);

//    std::vector<std::vector<int>> vec {
//           {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//           {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//           {1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,1},
//           {1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1},
//           {1,0,1,0,1,1,1,1,1,1,1,1,0,1,0,1},
//           {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//           {1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1},
//           {1,0,1,0,1,1,1,1,1,1,1,1,0,1,0,1},
//           {1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1},
//           {1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
//           {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//           {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//       };
//       drawMap(vec);
}

Game::~Game()
{

}

void Game::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Right)
        m_player->MoveRight();

    if(event->key() == Qt::Key_Left)
        m_player->MoveLeft();

    if(event->key() == Qt::Key_Up)
        m_player->MoveUp();

    if(event->key() == Qt::Key_Down)
        m_player->MoveDown();
}


//void Game::drawMap(const std::vector<std::vector<int>> &vec)
//{

//    for (int y = 0, n = 15; y < n; y++)
//        for (int x = 0, p = 15; x < p; x++)
//            if (vec[y][x] != 0)
//                fill(x,y);
//}
//void Game::fill( int x,  int y){
// //   pathingMap_.fillCell(x,y);
//    QGraphicsRectItem* rect = new QGraphicsRectItem(0,0,50,50);
//    rect->setPos(x*50,y*50);
//    QBrush brush;
//    brush.setColor(Qt::gray);
//    brush.setStyle(Qt::SolidPattern);
//    rect->setBrush(brush);
//    scene->addItem(rect);
//}
