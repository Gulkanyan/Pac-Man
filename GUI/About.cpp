#include "About.h"
#include "ui_About.h"
#include <QColorDialog>
#include "MainWindow.h"
About::About(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    setFixedSize(800,800);
    setStyleSheet("background-color:black;");
    setAutoFillBackground( true );
    ui->label->setPixmap(QPixmap(":/images/Images/mainBackground.jpg"));

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
    this->~About();
}
