#include "Dialog.h"
#include "ui_Dialog.h"

#include "CoreGlobals.h"

Dialog::Dialog(int currentPlayerScore, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    m_score = currentPlayerScore;
}

void Dialog::InitUi()
{
    this->setWindowIcon(QIcon(":/images/Images/logo.jpg"));
    this->setWindowTitle("Player Name");
    ui->pushButton->setShortcut(Qt::Key_Enter);

    if(CoreGlobals::gameSettings.language == Armenian)
    {
        this->setWindowTitle(QString::fromUtf8("Խաղացողի անունը"));
        ui->pushButton->setText(QString::fromUtf8("Հետ"));
    }
    else if(CoreGlobals::gameSettings.language == Russian)
    {
        this->setWindowTitle(QString::fromUtf8("Имя игрока"));
        ui->pushButton->setText(QString::fromUtf8("Назад"));
    }
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
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
