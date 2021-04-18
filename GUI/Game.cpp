#include "Game.h"
#include "Utils/Levels.h"
#include "GlobalDefs.h"
#include "Utils/Directions.h"
#include "StandardBlock.h"
#include "Core/Utils/Coin.h"
#include "Core/Utils/Pill.h"
#include "GlobalDefs.h"
#include "ShowPoint.h"

#include <QTimer>


namespace
{
    QTimer *m_tmr;
    Directions m_directions = Directions::Up;
    Directions m_previousDirection = Directions::Up;
    bool m_IsMovementEnabled = true;
    int m_counter = 0;
}

Game::Game(QWidget *parent) :
    QGraphicsView(parent),
    scene(new QGraphicsScene(this))
{
    InitInterface();

    AddPlayer();

    AddEnemies();

    DrawMap(Levels::level);

    InitMovementTimer();

    addScore();

}

void Game::InitInterface()
{
    scene = new QGraphicsScene(0,0,1090,790);
    setScene(scene);
    setFixedSize(1100,800);
    setStyleSheet("background-color:black;");
    setAutoFillBackground( true );
}

void Game::AddPlayer()
{
    m_player = new Player();
    m_player->setPos(350, 150);
    scene->addItem(m_player);
}



void Game::AddEnemies()
{
    m_red = new Red();
    m_red->setPos(350,350);
    scene->addItem(m_red);

    m_orange = new Orange();
    m_orange->setPos(400,350);
    scene->addItem(m_orange);

    m_blue = new Blue();
    m_blue->setPos(350,400);
    scene->addItem(m_blue);

    m_purple = new Purple();
    m_purple->setPos(400,400);
    scene->addItem(m_purple);

}
void Game::addScore()
{
    m_showpoint = new ShowPoint();
    m_showpoint->setPos(850,30);
    scene->addItem(m_showpoint);
}

void Game::InitMovementTimer()
{
    m_tmr = new QTimer();
    connect(m_tmr, SIGNAL(timeout()), this, SLOT(DoMovement()));
    m_tmr->start(100);
}

Game::~Game()
{
    delete m_tmr;
    delete m_player;
    delete m_red;
    delete m_blue;
    delete m_purple;
    delete m_orange;
    scene->clear();
    delete scene;
}

void Game::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Right:
            m_directions = Directions::Right;
            m_IsMovementEnabled = true;
        break;

        case Qt::Key_Left:
            m_directions = Directions::Left;
            m_IsMovementEnabled = true;
        break;

        case Qt::Key_Up:
            m_directions = Directions::Up;
            m_IsMovementEnabled = true;
        break;

        case Qt::Key_Down:
            m_directions = Directions::Down;
            m_IsMovementEnabled = true;
        break;
    }
}

void Game::DoMovement()
{
    if(m_IsMovementEnabled == false)
        return;

    if(m_counter == 0)
    {
        m_previousDirection = m_directions;
        m_counter = 5;
    }

    if(m_previousDirection == Directions::Right)
    {
        if(m_player->IsCollided(Directions::Right))
        {
            m_IsMovementEnabled = false;
            m_counter = 0;
            return;
        }
        m_player->MoveRight();
        m_counter--;
    }
    else if(m_previousDirection == Directions::Left)
    {
        if(m_player->IsCollided(Directions::Left))
        {
            m_IsMovementEnabled = false;
            m_counter = 0;
            return;
        }
        m_player->MoveLeft();
        m_counter--;
    }
    else if(m_previousDirection == Directions::Up)
    {
        if(m_player->IsCollided(Directions::Up))
        {
            m_IsMovementEnabled = false;
            m_counter = 0;
            return;
        }
        m_player->MoveUp();
        m_counter--;
    }
    else if(m_previousDirection == Directions::Down)
    {
        if(m_player->IsCollided(Directions::Down))
        {
            m_IsMovementEnabled = false;
            m_counter = 0;
            return;
        }
        m_player->MoveDown();
        m_counter--;
    }
    else
        qDebug() << "Direction is unknown\n";
}

void Game::DrawMap(const std::vector<std::vector<int>> &vec)
{
    for (size_t i = 0; i < vec.at(0).size(); ++i)
        for (size_t j = 0; j < vec.size(); ++j)
        {
            if (vec[j][i] == 1)
                fill(i, j);

            if (vec[j][i] == 0)
                fill_Coin(i,j);

            if(vec[j][i] == 2)
                fill_Pill(i,j);



        }


}

void Game::fill_Coin(int x, int y)
{
    Coin *coin = new Coin();
    coin->SetPosition(x * 50, y * 50);
    scene->addItem(coin);

}

void Game::fill_Pill(int x, int y)
{
    Pill *pill = new Pill();
    pill->SetPosition(x * 50, y * 50);
    scene->addItem(pill);


}

void Game::fill(int x, int y)
{
    StandardBlock *block = new StandardBlock();
    block->SetPosition(x * 50, y * 50);
    scene->addItem(block);
}
