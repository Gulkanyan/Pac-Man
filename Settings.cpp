#include "Settings.h"
#include "ui_Settings.h"
#include "MainWindow.h"

Settings::Settings(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    setFixedSize(800,800);
    setStyleSheet("background-color:black;");
    setAutoFillBackground( true );
    QPixmap pix1(":/images/Images/Pac-Man-Neon-Sign-474.jpg");
    ui->label->setPixmap(pix1);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::on_pushButton_clicked()
{
    MainWindow * main = new MainWindow();
    main->show();
    this->close();
    this->~Settings();
}
