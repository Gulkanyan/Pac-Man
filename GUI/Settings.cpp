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

    QStringList items;
    if(CoreGlobals::gameSettings.language == Armenian)
    {
        ui->LangComboBox->clear();
        items.append(QString::fromUtf8("Հայերեն"));
        items.append(QString::fromUtf8("Ռուսերեն"));
        items.append(QString::fromUtf8("Անգլերեն"));
        this->setWindowTitle(QString::fromUtf8("Կարգավորումներ"));
        ui->Sound->setText(QString::fromUtf8("Ձայն"));
        ui->LanguagesLabel->setText(QString::fromUtf8("Լեզու"));
        ui->LevelDifficulty->setText(QString::fromUtf8("Բարդության մակարդակ"));
        ui->turnOn->setText(QString::fromUtf8("Միացնել"));
        ui->turnOff->setText(QString::fromUtf8("Անջատել"));
        ui->easy->setText(QString::fromUtf8("Հեշտ"));
        ui->normal->setText(QString::fromUtf8("Միջին"));
        ui->Hard->setText(QString::fromUtf8("Բարդ"));
        ui->pushButton->setText(QString::fromUtf8("Հետ"));
    }
    else if(CoreGlobals::gameSettings.language == Russian)
    {
        ui->LangComboBox->clear();
        items.append(QString::fromUtf8("Армянский"));
        items.append(QString::fromUtf8("Русский"));
        items.append(QString::fromUtf8("Английский"));
        this->setWindowTitle(QString::fromUtf8("Настройки"));
        ui->Sound->setText(QString::fromUtf8("Звук"));
        ui->LanguagesLabel->setText(QString::fromUtf8("Язык"));
        ui->LevelDifficulty->setText(QString::fromUtf8("Уровень сложности"));
        ui->turnOn->setText(QString::fromUtf8("Включать"));
        ui->turnOff->setText(QString::fromUtf8("Выключать"));
        ui->easy->setText(QString::fromUtf8("Легкий"));
        ui->normal->setText(QString::fromUtf8("Обычный"));
        ui->Hard->setText(QString::fromUtf8("Сложный"));
        ui->pushButton->setText(QString::fromUtf8("Назад"));
    }
    ui->LangComboBox->addItems(items);

    switch(CoreGlobals::gameSettings.language)
    {
        case Armenian : ui->LangComboBox->setCurrentIndex(0); break;
        case Russian : ui->LangComboBox->setCurrentIndex(1); break;
        case English : ui->LangComboBox->setCurrentIndex(2); break;
        default : ui->LangComboBox->setCurrentIndex(0); break;
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

void Settings::on_LangComboBox_currentIndexChanged(int index)
{
    switch(index)
    {
        case 0 : CoreGlobals::gameSettings.language = Languages::Armenian; break;
        case 1 : CoreGlobals::gameSettings.language = Languages::Russian; break;
        case 2 : CoreGlobals::gameSettings.language = Languages::English; break;
        default : CoreGlobals::gameSettings.language = Languages::Armenian; break;
    }
}
