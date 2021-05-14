#include "About.h"
#include "ui_About.h"
#include <QColorDialog>

#include "MainWindow.h"
#include "CoreGlobals.h"

About::About(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);

    InitUi();
}

void About::InitUi()
{
    setStyleSheet("background-color:black;");
    setAutoFillBackground( true );
    ui->label->setPixmap(QPixmap(":/images/Images/mainBackground.jpg"));
    this->setWindowIcon(QIcon(":/images/Images/logo.jpg"));
    this->setWindowTitle("About Pac Man Qt");
    ui->pushButton->setShortcut(Qt::Key_Escape);

    if(CoreGlobals::gameSettings.language == Armenian)
    {
        this->setWindowTitle(QString::fromUtf8("Pac Man Qt - ի մասին"));
        ui->pushButton->setText(QString::fromUtf8("Հետ"));
        //ui->textEdit->setText(QString::fromUtf8("Ընտրեք ձեր ուրվականը"));
    }
    else if(CoreGlobals::gameSettings.language == Russian)
    {
        this->setWindowTitle(QString::fromUtf8("О Pac Man Qt"));
        ui->pushButton->setText(QString::fromUtf8("Назад"));
        //ui->textEdit->setText(QString::fromUtf8("Выбери своего призрака"));
    }
}

About::~About()
{
    delete ui;
}

void About::on_pushButton_clicked()
{
    MainWindow * main = new MainWindow();
    main->show();
    this->close();
    delete this;
}
