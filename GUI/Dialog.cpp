#include "Dialog.h"
#include "ui_Dialog.h"

#include <QtDebug>

#include "CoreGlobals.h"

Dialog::Dialog(int currentPlayerScore, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    m_score = currentPlayerScore;
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    qDebug() << "name of player :::: " << ui->lineEdit->text();

    if(ui->lineEdit->text().length() < 1)
    {
        return;
    }

    Score newScore;
    newScore.name = ui->lineEdit->text();
    newScore.score = m_score;

    db().AddNewScore(newScore);

    delete this;
}
