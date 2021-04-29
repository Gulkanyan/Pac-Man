#include "ScoresPage.h"
#include "ui_ScoresPage.h"

ScoresPage::ScoresPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ScoresPage)
{
    ui->setupUi(this);
}

ScoresPage::~ScoresPage()
{
    delete ui;
}
