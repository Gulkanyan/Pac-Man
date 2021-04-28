#include "Help.h"
#include "ui_Help.h"
#include "MainWindow.h"
#include <QSound>
Help::Help(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);
    setFixedSize(800,800);
    setStyleSheet("background-color:black;");
    setAutoFillBackground( true );
    ui->label->setPixmap(QPixmap(":/images/Images/mainBackground.jpg"));
    this->setWindowIcon(QIcon(":/images/Images/logo.jpg"));
    QSound::play(":/Sound/Music/pacman_beginning.wav");
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
