#include "Game.h"
#include "Utils/Levels.h"
#include "GlobalDefs.h"
#include "Utils/Directions.h"
#include "StandardBlock.h"

#include <QTimer>

namespace
{
    QTimer *m_tmr;
    Directions m_directions = Directions::Up;
    bool m_IsMovementEnabled = true;
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
}

void Game::InitInterface()
{
    scene = new QGraphicsScene(0,0,790,790);
    setScene(scene);
    setFixedSize(800,800);
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
    m_red->setPos(0,350);
    scene->addItem(m_red);
}

void Game::InitMovementTimer()
{
    m_tmr = new QTimer();
    connect(m_tmr, SIGNAL(timeout()), this, SLOT(DoMovement()));
    m_tmr->start(150);
}

Game::~Game()
{
    delete m_tmr;
    delete m_player;
    delete m_red;
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

    if(m_directions == Directions::Right)
    {
        if(m_player->IsCollided(Directions::Right))
        {
            m_IsMovementEnabled = false;
            return;
        }
        m_player->MoveRight();
    }
    else if(m_directions == Directions::Left)
    {
        if(m_player->IsCollided(Directions::Left))
        {
            m_IsMovementEnabled = false;
            return;
        }
        m_player->MoveLeft();
    }
    else if(m_directions == Directions::Up)
    {
        if(m_player->IsCollided(Directions::Up))
        {
            m_IsMovementEnabled = false;
            return;
        }
        m_player->MoveUp();
    }
    else if(m_directions == Directions::Down)
    {
        if(m_player->IsCollided(Directions::Down))
        {
            m_IsMovementEnabled = false;
            return;
        }
        m_player->MoveDown();
    }
    else
        qDebug() << "Direction is unknown\n";
}

void Game::DrawMap(const std::vector<std::vector<int>> &vec)
{
    for (size_t i = 0; i < vec.at(0).size(); ++i)
        for (size_t j = 0; j < vec.size(); ++j)
            if (vec[j][i] != 0)
                fill(i, j);
}

void Game::fill(int x, int y)
{
    StandardBlock *block = new StandardBlock();
    block->SetPosition(x * 50, y * 50);
    scene->addItem(block);
}
