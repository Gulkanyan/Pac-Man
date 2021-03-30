#include "Help.h"
#include "ui_Help.h"
#include "MainWindow.h"
Help::Help(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);
    setFixedSize(800,800);
    setStyleSheet("background-color:black;");
    setAutoFillBackground( true );
    QPixmap pix1(":/images/Images/Pac-Man-Neon-Sign-474.jpg");
    ui->label->setPixmap(pix1);
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
    this->~Help();

}
