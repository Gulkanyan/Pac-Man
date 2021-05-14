#include "Help.h"
#include "ui_Help.h"
#include "MainWindow.h"
#include "CoreGlobals.h"

Help::Help(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);
    setStyleSheet("background-color:black;");
    setAutoFillBackground( true );
    ui->label->setPixmap(QPixmap(":/images/Images/mainBackground.jpg"));
    this->setWindowIcon(QIcon(":/images/Images/logo.jpg"));
    if(CoreGlobals::gameSettings.musicIsEnabled)
        QSound::play(":/Sound/Music/pacman_beginning.wav");
    this->setWindowTitle("Help");
    ui->pushButton->setShortcut(Qt::Key_Escape);

    if(CoreGlobals::gameSettings.language == Armenian)
    {
        this->setWindowTitle(QString::fromUtf8("Օգնություն"));
        ui->pushButton->setText(QString::fromUtf8("Հետ"));
        ui->redLabel->setText(QString::fromUtf8("Կարմիր"));
        ui->blueLabel->setText(QString::fromUtf8("Կապույտ"));
        ui->orangeLabel->setText(QString::fromUtf8("Նարնջագույն"));
        ui->pinkLabel->setText(QString::fromUtf8("Մանուշակագույն"));
    }
    else if(CoreGlobals::gameSettings.language == Russian)
    {
        this->setWindowTitle(QString::fromUtf8("Помощь"));
        ui->pushButton->setText(QString::fromUtf8("Назад"));
        ui->redLabel->setText(QString::fromUtf8("Красный"));
        ui->blueLabel->setText(QString::fromUtf8("Синий"));
        ui->orangeLabel->setText(QString::fromUtf8("Оранжевый"));
        ui->pinkLabel->setText(QString::fromUtf8("Фиолетовый"));
    }
}

Help::~Help()
{
    delete ui;
}

void Help::on_pushButton_clicked()
{
    MainWindow *main = new MainWindow();
    main->show();
    this->close();
    delete this;
}
