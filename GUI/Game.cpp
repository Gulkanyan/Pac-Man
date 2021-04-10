#include "Game.h"
#include "ui_Game.h"

Game::Game(QWidget *parent) :
    QGraphicsView(parent)
{
    scene = new QGraphicsScene(0,0,790,790);
    setScene(scene);
    setFixedSize(800,800);
    setStyleSheet("background-color:black;");
    setAutoFillBackground( true );

    m_player = new Player();
    m_player->setPos(50,350);
    scene->addItem(m_player);
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

