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
    ui->label->setPixmap(QPixmap(":/images/Images/mainBackground.jpg"));
    this->setWindowIcon(QIcon(":/images/Images/logo.jpg"));

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
