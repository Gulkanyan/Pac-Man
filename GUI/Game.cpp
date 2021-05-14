#include "Game.h"
#include "Utils/StandardBlock.h"
#include "Core/Utils/Coin.h"
#include "Core/Utils/Pill.h"
#include "CoreGlobals.h"
#include "Player.h"
#include "MainWindow.h"
#include "Dialog.h"

#include <QTimer>

namespace
{
    QTimer *m_playerTimer;
    QTimer *m_enemysTimer;
    QSound m_beggining_sound(":/Sound/Music/pacman_beginning.wav");
    int m_coinsCount = 0;
    int m_currentLevel = 0;
    Directions m_manualDirectionForEnemy = Unknown;
}

Game::Game(QWidget *parent) :
    QGraphicsView(parent),
    scene(new QGraphicsScene(this))
{
    InitInterface();

    AddPlayer();

    DrawMap(Levels::level);

    InitPlayerTimer(PLAYER_TIMER_DEF_TIMEOUT);

    AddEnemies();

    if(CoreGlobals::multiplayerSettings.isEnabled == true)
    {
        InitEnemysTimer(PLAYER_TIMER_DEF_TIMEOUT - 20);

        connect(m_player, SIGNAL(GhostHealthisUpdated(int)), this, SLOT(UpdateGhostHealth(int)));
    }
    else
    {
        InitEnemysTimer(ENEMYS_TIMER_DEF_TIMEOUT);
    }

    if(CoreGlobals::gameSettings.musicIsEnabled)
        m_beggining_sound.play();

    connect(m_player, SIGNAL(ScoreIsUpdated(int)), this, SLOT(UpdateScore(int)));
    connect(m_player, SIGNAL(HealthIsUpdated(int)), this, SLOT(UpdateHealth(int)));
    connect(m_player, SIGNAL(PillIsEaten()), this, SLOT(GoToFrightenedMode()));
}

void Game::InitInterface()
{
    scene = new QGraphicsScene(0,0,680,550);
    setScene(scene);
    setFixedSize(690,560);
    setStyleSheet("background-color:black;");
    setAutoFillBackground( true );
    this->setWindowIcon(QIcon(":/images/Images/logo.jpg"));

    m_scoreText = new QGraphicsTextItem();
    m_scoreText->setDefaultTextColor(Qt::cyan);
    m_scoreText->setFont(QFont("times",16));
    m_scoreText->setPos(480,30);
    scene->addItem(m_scoreText);

    m_healthText = new QGraphicsTextItem();
    m_healthText->setDefaultTextColor(Qt::cyan);
    m_healthText-> setFont(QFont("times",16));
    m_healthText->setPos(480, 100);
    if(CoreGlobals::gameSettings.language == Languages::Armenian)
        m_healthText->setPlainText(QString("Առողջություն: ")+ QString::number(5));
    else if(CoreGlobals::gameSettings.language == Languages::Russian)
        m_healthText->setPlainText(QString("Здоровье: ")+ QString::number(5));
    else if(CoreGlobals::gameSettings.language == Languages::English)
        m_healthText->setPlainText(QString("Health: ")+ QString::number(5));
    scene->addItem(m_healthText);

    if(CoreGlobals::multiplayerSettings.isEnabled)
    {
        m_enemyHealthText = new QGraphicsTextItem();
        m_enemyHealthText->setDefaultTextColor(Qt::cyan);
        m_enemyHealthText-> setFont(QFont("times",16));
        m_enemyHealthText->setPos(480, 170);
        if(CoreGlobals::gameSettings.language == Languages::Armenian)
            m_enemyHealthText->setPlainText(QString("Ուրվականի\nառողջություն: ")+ QString::number(CoreGlobals::multiplayerSettings.enemyLives));
        else if(CoreGlobals::gameSettings.language == Languages::Russian)
            m_enemyHealthText->setPlainText(QString("Здоровье\nпризрака: ")+ QString::number(CoreGlobals::multiplayerSettings.enemyLives));
        else if(CoreGlobals::gameSettings.language == Languages::English)
            m_enemyHealthText->setPlainText(QString("Ghost\nHealth: ")+ QString::number(CoreGlobals::multiplayerSettings.enemyLives));
        scene->addItem(m_enemyHealthText);
    }
}

void Game::AddPlayer()
{
    m_player = new Player();
    m_player->setPos(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);
    scene->addItem(m_player);
}

void Game::AddEnemies()
{
    m_red = nullptr;
    m_blue = nullptr;
    m_orange = nullptr;
    m_purple = nullptr;

    if(CoreGlobals::multiplayerSettings.isEnabled && CoreGlobals::multiplayerSettings.selectedGhost != Unknown_Ghost)
    {
        m_red = new Red();
        scene->addItem(m_red);
        m_red->setPos(DEFAULT_BLOCK_SIZE*17, DEFAULT_BLOCK_SIZE*20);
        return;
    }

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
    m_coinsCount--;
    m_scoreText->setPlainText("");

    if(CoreGlobals::gameSettings.language == Languages::Armenian)
        m_scoreText->setPlainText(QString("Միավորներ: ")+ QString::number(score));
    else if(CoreGlobals::gameSettings.language == Languages::Russian)
        m_scoreText->setPlainText(QString("Очки: ")+ QString::number(score));
    else if(CoreGlobals::gameSettings.language == Languages::English)
        m_scoreText->setPlainText(QString("Score: ")+ QString::number(score));
}

void Game::UpdateHealth(int health)
{
    m_healthText->setPlainText("");
    if(CoreGlobals::gameSettings.language == Languages::Armenian)
        m_healthText->setPlainText(QString("Առողջություն: ")+ QString::number(health));
    else if(CoreGlobals::gameSettings.language == Languages::Russian)
        m_healthText->setPlainText(QString("Здоровье: ")+ QString::number(health));
    else if(CoreGlobals::gameSettings.language == Languages::English)
        m_healthText->setPlainText(QString("Health: ")+ QString::number(health));

    if(health <= 0)
    {
        m_playerTimer->stop();
        m_enemysTimer->stop();

        if(CoreGlobals::multiplayerSettings.isEnabled == true)
        {
            if(CoreGlobals::gameSettings.language == Languages::Armenian)
                ShowMessageBox("Հաղթեց ուրվականը !!!");
            else if(CoreGlobals::gameSettings.language == Languages::Russian)
                ShowMessageBox("Призрак победил !!!");
            else if(CoreGlobals::gameSettings.language == Languages::English)
                ShowMessageBox("Ghost won!!!");
        }
        else
        {
            if(CoreGlobals::gameSettings.language == Languages::Armenian)
                ShowMessageBox("Խաղն ավարտված է!!!");
            else if(CoreGlobals::gameSettings.language == Languages::Russian)
                ShowMessageBox("Игра окончена!!!");
            else if(CoreGlobals::gameSettings.language == Languages::English)
                ShowMessageBox("Game Over!!!");

            GetPlayerNameAndSave();
        }

        MainWindow * main = new MainWindow();
        main->show();
        this->close();
        delete this;
        return;
    }

    if(m_red != nullptr)
        m_red->Reset();
    if(m_blue != nullptr)
        m_blue->Reset();
    if(m_orange != nullptr)
        m_orange->Reset();
    if(m_purple != nullptr)
        m_purple->Reset();
}

void Game::GoToFrightenedMode()
{
    if(m_red != nullptr)
        m_red->SetState(GhostsStates::Frightend);
    if(m_blue != nullptr)
        m_blue->SetState(GhostsStates::Frightend);
    if(m_orange != nullptr)
        m_orange->SetState(GhostsStates::Frightend);
    if(m_purple != nullptr)
        m_purple->SetState(GhostsStates::Frightend);
}

void Game::InitPlayerTimer(int msec)
{
    m_playerTimer = new QTimer();
    connect(m_playerTimer, SIGNAL(timeout()), this, SLOT(DoMovement()));
    m_playerTimer->start(msec);
}

void Game::InitEnemysTimer(int msec)
{
    m_enemysTimer = new QTimer();
    connect(m_enemysTimer, SIGNAL(timeout()), this, SLOT(DoEnemysMovement()));
    m_enemysTimer->start(msec);
}

Game::~Game()
{
    delete m_playerTimer;
    delete m_enemysTimer;
    delete m_scoreText;
    delete m_healthText;
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

        case Qt::Key_W:
            m_manualDirectionForEnemy = Directions::Up;
        break;

        case Qt::Key_A:
            m_manualDirectionForEnemy = Directions::Left;
        break;

        case Qt::Key_D:
            m_manualDirectionForEnemy = Directions::Right;
        break;

        case Qt::Key_S:
            m_manualDirectionForEnemy = Directions::Down;
        break;

        case Qt::Key_M:
            if(m_red != nullptr)
                m_red->ChangeStates();
            if(m_blue != nullptr)
                m_blue->ChangeStates();
            if(m_orange != nullptr)
                m_orange->ChangeStates();
            if(m_purple != nullptr)
                m_purple->ChangeStates();
        break;

        case Qt::Key_Escape:
            if(DoYouWantToExit())
            {
                MainWindow * main = new MainWindow();
                main->show();
                this->close();
                delete this;
            }
        break;
    }
}

void Game::DoMovement()
{
    m_player->DoMovement();

    if(m_coinsCount <= 0)
    {
        if(CoreGlobals::multiplayerSettings.isEnabled == true)
        {
            if(CoreGlobals::gameSettings.language == Languages::Armenian)
                ShowMessageBox("Pac Man - ը հաղթեց");
            else if(CoreGlobals::gameSettings.language == Languages::Russian)
                ShowMessageBox("Pac Man выиграл !!!");
            else if(CoreGlobals::gameSettings.language == Languages::English)
                ShowMessageBox("Pac Man won !!!");
        }
        else
            NextLevel();
    }
}

void Game::DoEnemysMovement()
{
    CoreGlobals::playersCoords.x = m_player->x() / DEFAULT_BLOCK_SIZE;
    CoreGlobals::playersCoords.y = m_player->y() / DEFAULT_BLOCK_SIZE;

    if(m_red != nullptr)
        m_red->DoMove(m_manualDirectionForEnemy);
    if(m_blue != nullptr)
        m_blue->DoMove(m_player->m_directions);
    if(m_orange != nullptr)
        m_orange->DoMove(m_player->m_directions);
    if(m_purple != nullptr)
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
    m_coinsCount++;
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

void Game::NextLevel()
{
    m_currentLevel++;

    m_playerTimer->stop();
    m_enemysTimer->stop();

    m_player->setPos(DEFAULT_BLOCK_SIZE, DEFAULT_BLOCK_SIZE);

    if(m_red != nullptr)
    {
        m_red->setPos(9 * DEFAULT_BLOCK_SIZE, 9 * DEFAULT_BLOCK_SIZE);
        m_red->SetCounter(0);
        m_red->SetState(GhostsStates::Chase);
    }
    if(m_blue != nullptr)
    {
        m_blue->setPos(10 * DEFAULT_BLOCK_SIZE, 10 * DEFAULT_BLOCK_SIZE);
        m_blue->SetCounter(0);
        m_blue->SetState(GhostsStates::Chase);
    }
    if(m_orange != nullptr)
    {
        m_orange->setPos(9 * DEFAULT_BLOCK_SIZE, 10 * DEFAULT_BLOCK_SIZE);
        m_orange->SetCounter(0);
        m_orange->SetState(GhostsStates::Chase);
    }
    if(m_purple != nullptr)
    {
        m_purple->setPos(10 * DEFAULT_BLOCK_SIZE, 9 * DEFAULT_BLOCK_SIZE);
        m_purple->SetCounter(0);
        m_purple->SetState(GhostsStates::Chase);
    }

    for (size_t i = 0; i < Levels::level.at(0).size(); ++i)
        for (size_t j = 0; j < Levels::level.size(); ++j)
        {

            if(Levels::level[j][i] == 0)
                fill_Coin(i,j);

            if(Levels::level[j][i] == 2)
                fill_Pill(i,j);
        }

    if(PLAYER_TIMER_DEF_TIMEOUT - m_currentLevel * 10 <= 0)
        m_playerTimer->start(1);
    else
        m_playerTimer->start(PLAYER_TIMER_DEF_TIMEOUT - m_currentLevel * 10);

    if(ENEMYS_TIMER_DEF_TIMEOUT - m_currentLevel * 20 <= 0)
        m_enemysTimer->start(1);
    else
        m_enemysTimer->start(ENEMYS_TIMER_DEF_TIMEOUT - m_currentLevel * 20);
}

bool Game::DoYouWantToExit()
{
    m_playerTimer->stop();
    m_enemysTimer->stop();
    QMessageBox *box = new QMessageBox();

    if(CoreGlobals::gameSettings.language == Languages::Armenian)
        box->setText("<center>Ուզու՞մ եք դուրս գալ</center>");
    else if(CoreGlobals::gameSettings.language == Languages::Russian)
        box->setText("<center>Вы хотите выйти?</center>");
    else if(CoreGlobals::gameSettings.language == Languages::English)
        box->setText("<center>Do you want to exit?</center>");

    box->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    box->setStyleSheet(QString("QMessageBox {"
                                 "background-color: rgb(255, 255, 255);"
                                 "font-size: 20pt;"
                                 "}"
                                  "QMessageBox QPushButton { color: blue; background-color: white;"
                                  "width: 150px; height: 35px;}"
                                  ));

    QString btnText = "Yes";
    if(CoreGlobals::gameSettings.language == Languages::Armenian)
        btnText = "Այո";
    else if(CoreGlobals::gameSettings.language == Languages::Russian)
        btnText = "Да";
    else if(CoreGlobals::gameSettings.language == Languages::English)
        btnText = "Yes";
    QPushButton *pButtonYes = box->addButton(btnText, QMessageBox::AcceptRole);
    pButtonYes->setStyleSheet("QPushButton{color: rgb(255, 255, 255); background-color: rgba(180, 0, 0, 180); border-style: outset; border-width: 2px; border-radius: 10px; border-color: beige; font: bold 14px; min-width: 10em; padding: 6px;}"
                              "QPushButton::pressed {color: rgb(255, 255, 255); background-color: rgba(150, 0, 0, 130); border-style: inset;}");

    if(CoreGlobals::gameSettings.language == Languages::Armenian)
        btnText = "Ոչ";
    else if(CoreGlobals::gameSettings.language == Languages::Russian)
        btnText = "Нет";
    else if(CoreGlobals::gameSettings.language == Languages::English)
        btnText = "No";
    QPushButton *pButtonNo = box->addButton(btnText, QMessageBox::AcceptRole);
    pButtonNo->setStyleSheet("QPushButton{color: rgb(255, 255, 255); background-color: rgba(0, 180, 0, 180); border-style: outset; border-width: 2px; border-radius: 10px; border-color: beige; font: bold 14px; min-width: 10em; padding: 6px;}"
                             "QPushButton::pressed {color: rgb(255, 255, 255); background-color: rgba(0, 150, 0, 130); border-style: inset;}");
    pButtonNo->setShortcut(Qt::Key_Escape);
    bool accept = box->exec() == QMessageBox::AcceptRole;
    if(!accept)
    {
        m_playerTimer->start();
        m_enemysTimer->start();
    }

    delete box;
    return accept;
}

void Game::ShowMessageBox(QString message)
{
    QMessageBox *box = new QMessageBox();
    box->setText("<center>" + message + "</center>");
    box->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    box->setStyleSheet(QString("QMessageBox {"
                                 "background-color: rgb(255, 255, 255);"
                                 "font-size: 20pt;"
                                 "}"
                                  "QMessageBox QPushButton { color: blue; background-color: white;"
                                  "width: 150px; height: 35px;}"
                                  ));

    QString btnText = "Yes";
    if(CoreGlobals::gameSettings.language == Languages::Armenian)
        btnText = "Այո";
    else if(CoreGlobals::gameSettings.language == Languages::Russian)
        btnText = "Да";
    else if(CoreGlobals::gameSettings.language == Languages::English)
        btnText = "Yes";
    QPushButton *pButtonOk = box->addButton(btnText, QMessageBox::AcceptRole);
    pButtonOk->setStyleSheet("QPushButton{color: rgb(255, 255, 255); background-color: rgba(0, 180, 0, 180); border-style: outset; border-width: 2px; border-radius: 10px; border-color: beige; font: bold 14px; min-width: 10em; padding: 6px;}"
                             "QPushButton::pressed {color: rgb(255, 255, 255); background-color: rgba(0, 150, 0, 130); border-style: inset;}");
    pButtonOk->setShortcut(Qt::Key_Enter);
    box->exec();

    delete box;
}

void Game::GetPlayerNameAndSave()
{
    Dialog *dialog = new Dialog(m_player->GetScore());
    dialog->exec();
    return;
}

void Game::UpdateGhostHealth(int health)
{
    m_enemyHealthText->setPlainText("");

    if(CoreGlobals::gameSettings.language == Languages::Armenian)
        m_enemyHealthText->setPlainText(QString("Ուրվականի\nառողջություն: ")+ QString::number(health));
    else if(CoreGlobals::gameSettings.language == Languages::Russian)
        m_enemyHealthText->setPlainText(QString("Здоровье\nпризрака: ")+ QString::number(health));
    else if(CoreGlobals::gameSettings.language == Languages::English)
        m_enemyHealthText->setPlainText(QString("Ghost\nHealth: ")+ QString::number(health));

    if(health <= 0)
    {
        m_playerTimer->stop();
        m_enemysTimer->stop();

        if(CoreGlobals::gameSettings.language == Languages::Armenian)
            ShowMessageBox("Pac Man - ը հաղթեց");
        else if(CoreGlobals::gameSettings.language == Languages::Russian)
            ShowMessageBox("Pac Man выиграл !!!");
        else if(CoreGlobals::gameSettings.language == Languages::English)
            ShowMessageBox("Pac Man won !!!");

        MainWindow * main = new MainWindow();
        main->show();
        this->close();
        delete this;
        return;
    }

    if(m_red != nullptr)
        m_red->Reset();
    if(m_blue != nullptr)
        m_blue->Reset();
    if(m_orange != nullptr)
        m_orange->Reset();
    if(m_purple != nullptr)
        m_purple->Reset();
}
