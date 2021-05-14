#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Game.h"
#include "About.h"
#include "Settings.h"
#include "Help.h"
#include "Player.h"
#include "ScoresPage.h"
#include "ChooseGhost.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    InitPage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitPage()
{
    ui->setupUi(this);
    setStyleSheet("background-color:black;");
    setAutoFillBackground( true );
    ui->label->setPixmap(QPixmap(":/images/Images/mainBackground.jpg"));
    this->setWindowIcon(QIcon(":/images/Images/logo.jpg"));
    this->setWindowTitle("Pac Man Qt");

    if(CoreGlobals::gameSettings.language == Armenian)
    {
        ui->play->setText(QString::fromUtf8("Խաղալ"));
        ui->pushButton->setText(QString::fromUtf8("Խաղալ ընկերոջ հետ"));
        ui->about->setText(QString::fromUtf8("Խաղի մասին"));
        ui->settings->setText(QString::fromUtf8("Կարգավորումներ"));
        ui->help->setText(QString::fromUtf8("Օգնություն"));
        ui->soresPageBtn->setText(QString::fromUtf8("Միավորներ"));
    }
    else if(CoreGlobals::gameSettings.language == Russian)
    {
        ui->play->setText(QString::fromUtf8("Играть"));
        ui->pushButton->setText(QString::fromUtf8("Играть с другом"));
        ui->about->setText(QString::fromUtf8("Об игре"));
        ui->settings->setText(QString::fromUtf8("Настройки"));
        ui->help->setText(QString::fromUtf8("Помощь"));
        ui->soresPageBtn->setText(QString::fromUtf8("Очки"));
    }
}

void MainWindow::on_play_clicked()
{
    CoreGlobals::multiplayerSettings.isEnabled = false;
    CoreGlobals::multiplayerSettings.selectedGhost = Ghosts::Unknown_Ghost;
    Game *game = new Game();
    game->show();
    this->close();
    delete this;
}

void MainWindow::on_about_clicked()
{
    About *about = new About();
    about->show();
    this->close();
    delete this;
}

void MainWindow::on_settings_clicked()
{
    Settings *settings= new Settings();
    settings->show();
    this->close();
    delete this;
}

void MainWindow::on_help_clicked()
{
    Help *help=new Help();
    help->show();
    this->close();
    delete this;
}

void MainWindow::on_soresPageBtn_clicked()
{
    ScoresPage *scores = new ScoresPage();
    scores->show();
    this->close();
    delete this;
}

void MainWindow::on_pushButton_clicked()
{
    ChooseGhost *chooseghost = new ChooseGhost(this);
    chooseghost->show();
}

void MainWindow::StartMultiplayer()
{
    Game *game = new Game();
    game->show();
    this->close();
    this->deleteLater();
}
