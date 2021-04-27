#include "Game.h"
#include "Utils/StandardBlock.h"
#include "Core/Utils/Coin.h"
#include "Core/Utils/Pill.h"
#include "CoreGlobals.h"

#include <QTimer>
#include <QSound>
#include <QMainWindow>

namespace
{
    QTimer *m_playerTimer;
    QTimer *m_enemysTimer;
    QSound m_beggining_sound(":/Sound/Music/pacman_beginning.wav");
}

Game::Game(QWidget *parent) :
    QGraphicsView(parent),
    scene(new QGraphicsScene(this))
{
    InitInterface();

    AddPlayer();

    DrawMap(Levels::level);

    InitPlayerTimer();

    AddEnemies();

    InitEnemysTimer();
    m_beggining_sound.play();

    connect(m_player, SIGNAL(ScoreIsUpdated(int)), this, SLOT(UpdateScore(int)));
    connect(m_player, SIGNAL(HealthIsUpdated(int)), this, SLOT(UpdateHealth(int)));
}

void Game::InitInterface()
{
    scene = new QGraphicsScene(0,0,650,550);
    setScene(scene);
    setFixedSize(660,560);
    setStyleSheet("background-color:black;");
    setAutoFillBackground( true );
    this->setWindowIcon(QIcon(":/images/Images/logo.jpg"));

    m_scoreText = new QGraphicsTextItem();
    m_scoreText->setDefaultTextColor(Qt::cyan);
    m_scoreText->setFont(QFont("times",16));
    m_scoreText->setPos(500,30);
    scene->addItem(m_scoreText);

    m_healthText = new QGraphicsTextItem();
    m_healthText->setDefaultTextColor(Qt::cyan);
    m_healthText-> setFont(QFont("times",16));
    m_healthText->setPos(500, 100);
    m_healthText->setPlainText(QString("Health: ")+ QString::number(5));
    scene->addItem(m_healthText);
}

void Game::AddPlayer()
{
    m_player = new Player();
    m_player->setPos(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    scene->addItem(m_player);
}

void Game::AddEnemies()
{
    m_red = new Red();
    scene->addItem(m_red);

    m_orange = new Orange();
    scene->addItem(m_orange);

    m_blue = new Blue();
    scene->addItem(m_blue);

    m_purple = new Purple();
    scene->addItem(m_purple);
}

void Game::UpdateScore(int score)
{
    m_scoreText->setPlainText("");
    m_scoreText->setPlainText(QString("Միավոր: ")+ QString::number(score));
}

void Game::UpdateHealth(int health)
{
    m_healthText->setPlainText("");
    m_healthText->setPlainText(QString("Health: ")+ QString::number(health));
}

void Game::InitPlayerTimer()
{
    m_playerTimer = new QTimer();
    connect(m_playerTimer, SIGNAL(timeout()), this, SLOT(DoMovement()));
    m_playerTimer->start(100);
}

void Game::InitEnemysTimer()
{
    m_enemysTimer = new QTimer();
    connect(m_enemysTimer, SIGNAL(timeout()), this, SLOT(DoEnemysMovement()));
    m_enemysTimer->start(100);
}

Game::~Game()
{
    delete m_playerTimer;
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
            m_player->m_directions = Directions::Right;
            m_player->m_IsMovementEnabled = true;
        break;

        case Qt::Key_Left:
            m_player->m_directions = Directions::Left;
            m_player->m_IsMovementEnabled = true;
        break;

        case Qt::Key_Up:
            m_player->m_directions = Directions::Up;
            m_player->m_IsMovementEnabled = true;
        break;

        case Qt::Key_Down:
            m_player->m_directions = Directions::Down;
            m_player->m_IsMovementEnabled = true;
        break;

        case Qt::Key_M:
            m_purple->ChangeStates();
        break;
    }
}

void Game::DoMovement()
{
    m_player->DoMovement();
}

void Game::DoEnemysMovement()
{
    CoreGlobals::playersCoords.x = m_player->x() / DEFAULT_BLOCK_SIZE;
    CoreGlobals::playersCoords.y = m_player->y() / DEFAULT_BLOCK_SIZE;

    m_red->DoMove();

    m_blue->DoMove(m_player->m_directions);

    m_orange->DoMove(m_player->m_directions);

    m_purple->DoMove(m_player->m_directions);
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
    coin->SetPosition(x * DEFAULT_BLOCK_SIZE, y * DEFAULT_BLOCK_SIZE);
    scene->addItem(coin);
}

void Game::fill_Pill(int x, int y)
{
    Pill *pill = new Pill();
    pill->SetPosition(x * DEFAULT_BLOCK_SIZE, y * DEFAULT_BLOCK_SIZE);
    scene->addItem(pill);
}

void Game::fill(int x, int y)
{
    StandardBlock *block = new StandardBlock();
    block->SetPosition(x * DEFAULT_BLOCK_SIZE, y * DEFAULT_BLOCK_SIZE);
    scene->addItem(block);
}
