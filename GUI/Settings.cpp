#include "Settings.h"
#include "ui_Settings.h"
#include "MainWindow.h"
#include "CoreGlobals.h"

Settings::Settings(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    InitUi();
}

void Settings::InitUi()
{
    setStyleSheet("background-color:black;");
    setAutoFillBackground( true );
    ui->label->setPixmap(QPixmap(":/images/Images/mainBackground.jpg"));
    this->setWindowIcon(QIcon(":/images/Images/logo.jpg"));
    this->setWindowTitle("Settings");

    ui->pushButton->setShortcut(Qt::Key_Escape);

    if(CoreGlobals::gameSettings.musicIsEnabled)
        ui->turnOn->setChecked(true);
    else
        ui->turnOff->setChecked(true);

    switch (CoreGlobals::gameSettings.complexityLevel)
    {
        case 0: ui->easy->setChecked(true); break;
        case 1: ui->normal->setChecked(true); break;
        case 2: ui->Hard->setChecked(true); break;
        default: ui->normal->setChecked(true); break;
    }
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
    delete this;
}

void Settings::on_turnOn_clicked()
{
    CoreGlobals::gameSettings.musicIsEnabled = true;
}

void Settings::on_turnOff_clicked()
{
    CoreGlobals::gameSettings.musicIsEnabled = false;
}

void Settings::on_easy_clicked()
{
    CoreGlobals::gameSettings.complexityLevel = 0;
}

void Settings::on_normal_clicked()
{
    CoreGlobals::gameSettings.complexityLevel = 1;
}

void Settings::on_Hard_clicked()
{
    CoreGlobals::gameSettings.complexityLevel = 2;
}
