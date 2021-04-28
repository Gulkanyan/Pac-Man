#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Game.h"
#include "About.h"
#include "Settings.h"
#include "Help.h"
#include <Player.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(800,800);
    setStyleSheet("background-color:black;");
    setAutoFillBackground( true );
    ui->label->setPixmap(QPixmap(":/images/Images/mainBackground.jpg"));
    this->setWindowIcon(QIcon(":/images/Images/logo.jpg"));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_play_clicked()
{
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
