#include "ChooseGhost.h"
#include "ui_ChooseGhost.h"
#include "Game.h"
ChooseGhost::ChooseGhost(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChooseGhost)
{
    ui->setupUi(this);
}

ChooseGhost::~ChooseGhost()
{
    delete ui;
}

void ChooseGhost::on_pushButton_clicked()
{
    Game *game = new Game();
    game->show();
    this->close();
    this->~ChooseGhost();

}
