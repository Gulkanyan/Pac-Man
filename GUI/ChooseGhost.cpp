#include "ChooseGhost.h"
#include "ui_ChooseGhost.h"

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
