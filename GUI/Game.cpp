#include "Game.h"
#include "Utils/Levels.h"
#include "GlobalDefs.h"

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

    m_red = new  Red();
    m_red ->setPos(0,350);
    scene->addItem(m_red);

    drawMap(Levels::level);
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

void Game::drawMap(const std::vector<std::vector<int>> &vec)
{
    DEBUG_LOG;

    for (size_t i = 0; i < vec.at(0).size(); ++i)
        for (size_t j = 0; j < vec.size(); ++j)
            if (vec[j][i] != 0)
                fill(i, j);
}

void Game::fill(int x, int y)
{
    QGraphicsRectItem* rect = new QGraphicsRectItem(x * 50, y * 50, 50, 50);
    QBrush brush;
    brush.setColor(Qt::gray);
    brush.setStyle(Qt::SolidPattern);
    rect->setBrush(brush);
    scene->addItem(rect);
}
