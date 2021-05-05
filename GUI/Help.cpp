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
