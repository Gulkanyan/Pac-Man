#include "Game.h"
#include "ui_Game.h"
#include "Player.h"
Game::Game(QWidget *parent) :
    QGraphicsView(parent)
{

    scene = new QGraphicsScene(0,0,800,800);
    setScene(scene);
    setFixedSize(800,800);
    setStyleSheet("background-color:black;");
    setAutoFillBackground( true );


    Player* player = new Player();
    player->setPos(50,350);
    scene->addItem(player);



}

Game::~Game()
{

}
