#include "ScoresPage.h"
#include "ui_ScoresPage.h"

#include "MainWindow.h"
#include "CoreGlobals.h"

ScoresPage::ScoresPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ScoresPage)
{
    ui->setupUi(this);

    InitUi();

    InitData();
}

void ScoresPage::InitUi()
{
    setStyleSheet("background-color:black;");
    setAutoFillBackground( true );
    ui->label->setPixmap(QPixmap(":/images/Images/mainBackground.jpg"));
    this->setWindowIcon(QIcon(":/images/Images/logo.jpg"));
    if(CoreGlobals::gameSettings.musicIsEnabled)
        QSound::play(":/Sound/Music/pacman_beginning.wav");
    this->setWindowTitle("Scores");
    ui->pushButton->setShortcut(Qt::Key_Escape);

    if(CoreGlobals::gameSettings.language == Armenian)
    {
        this->setWindowTitle(QString::fromUtf8("Միավորներ"));
        ui->top5Label->setText(QString::fromUtf8("Թոփ 5"));
        ui->pushButton->setText(QString::fromUtf8("Հետ"));
        ui->bestLabel->setText(QString::fromUtf8("Լավագույն միավոր"));
    }
    else if(CoreGlobals::gameSettings.language == Russian)
    {
        this->setWindowTitle(QString::fromUtf8("Очки"));
        ui->top5Label->setText(QString::fromUtf8("Топ 5"));
        ui->pushButton->setText(QString::fromUtf8("Назад"));
        ui->bestLabel->setText(QString::fromUtf8("Лучший результат"));
    }
}

void ScoresPage::InitData()
{
    Score score;
    db().GetBestScoreAndName(score);

    ui->bestNameLabel->setText(score.name);
    ui->bestLcdNumber->display(score.score);

    QList<Score> top5Scores;
    db().GetTop5Scores(top5Scores);

    qDebug() << top5Scores.count();

    for(int i = 0; i < top5Scores.count(); ++i)
    {
        switch (i)
        {
            case 0:
                ui->top1NameLabel->setText(top5Scores.at(i).name);
                ui->top1LcdNumber->display(top5Scores.at(i).score);
            break;
            case 1:
                ui->top2NameLabel->setText(top5Scores.at(i).name);
                ui->top2LcdNumber->display(top5Scores.at(i).score);
            break;
            case 2:
                ui->top3NameLabel->setText(top5Scores.at(i).name);
                ui->top3LcdNumber->display(top5Scores.at(i).score);
            break;
            case 3:
                ui->top4NameLabel->setText(top5Scores.at(i).name);
                ui->top4LcdNumber->display(top5Scores.at(i).score);
            break;
            case 4:
                ui->top5NameLabel->setText(top5Scores.at(i).name);
                ui->top5LcdNumber->display(top5Scores.at(i).score);
            break;
        }
    }
}

ScoresPage::~ScoresPage()
{
    delete ui;
}

void ScoresPage::on_pushButton_clicked()
{
    MainWindow *mainPage = new MainWindow();
    mainPage->show();
    this->close();
    delete this;
}
