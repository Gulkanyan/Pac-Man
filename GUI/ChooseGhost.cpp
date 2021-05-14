#include "ChooseGhost.h"
#include "ui_ChooseGhost.h"

#include "CoreGlobals.h"
#include "MainWindow.h"

ChooseGhost::ChooseGhost(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChooseGhost)
{
    ui->setupUi(this);

    InitUi();

    connect(this, SIGNAL(StartMultiplayer()), reinterpret_cast<MainWindow *>(parent), SLOT(StartMultiplayer()));
}

void ChooseGhost::InitUi()
{
    this->setWindowIcon(QIcon(":/images/Images/logo.jpg"));
    this->setWindowTitle("Multiplayer Settings");
    ui->BackButton->setShortcut(Qt::Key_Escape);

    if(CoreGlobals::gameSettings.language == Armenian)
    {
        this->setWindowTitle(QString::fromUtf8("Ցանցային խաղի կարգաբերումներ"));
        ui->BackButton->setText(QString::fromUtf8("Հետ"));
        ui->pushButton->setText(QString::fromUtf8("Պահպանել"));
        ui->label->setText(QString::fromUtf8("Ընտրեք ձեր ուրվականը"));
        ui->RedRadioButton->setText(QString::fromUtf8("Կարմիր ուրվական"));
        ui->BlueRadioButton->setText(QString::fromUtf8("Կապույտ ուրվական"));
        ui->OrangeRadioButton->setText(QString::fromUtf8("Նարնջագույն ուրվական"));
        ui->PurpleRadioButton->setText(QString::fromUtf8("Մանուշակագույն ուրվական"));
    }
    else if(CoreGlobals::gameSettings.language == Russian)
    {
        this->setWindowTitle(QString::fromUtf8("Настройки сетевой игры"));
        ui->BackButton->setText(QString::fromUtf8("Назад"));
        ui->pushButton->setText(QString::fromUtf8("Сохранить"));
        ui->label->setText(QString::fromUtf8("Выбери своего призрака"));
        ui->RedRadioButton->setText(QString::fromUtf8("Красный Призрак"));
        ui->BlueRadioButton->setText(QString::fromUtf8("Синий призрак"));
        ui->OrangeRadioButton->setText(QString::fromUtf8("Оранжевый призрак"));
        ui->PurpleRadioButton->setText(QString::fromUtf8("Фиолетовый призрак"));
    }
}

ChooseGhost::~ChooseGhost()
{
    delete ui;
}

void ChooseGhost::on_pushButton_clicked()
{
    CoreGlobals::multiplayerSettings.isEnabled = true;

    if(ui->RedRadioButton->isChecked())
        CoreGlobals::multiplayerSettings.selectedGhost = Red_Ghost;
    else if(ui->BlueRadioButton->isChecked())
        CoreGlobals::multiplayerSettings.selectedGhost = Blue_Ghost;
    else if(ui->OrangeRadioButton->isChecked())
        CoreGlobals::multiplayerSettings.selectedGhost = Orange_Ghost;
    else if(ui->PurpleRadioButton->isChecked())
        CoreGlobals::multiplayerSettings.selectedGhost = Purple_Ghost;
    else
    {
        CoreGlobals::multiplayerSettings.isEnabled = false;
        ShowMessageBox();
        return;
    }
    emit StartMultiplayer();

    this->close();
    delete this;
}

void ChooseGhost::ShowMessageBox()
{
    QMessageBox *box = new QMessageBox();
    if(CoreGlobals::gameSettings.language == Armenian)
        box->setText("<center>Անհրաժեշտ է ընտրել ուրվականին</center>");
    else if(CoreGlobals::gameSettings.language == Russian)
        box->setText("<center>Необходимо выбрать призрака</center>");
    else if(CoreGlobals::gameSettings.language == English)
        box->setText("<center>Must choose a ghost</center>");
    box->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    box->setStyleSheet(QString("QMessageBox {"
                                 "background-color: rgb(255, 255, 255);"
                                 "font-size: 20pt;"
                                 "}"
                                  "QMessageBox QPushButton { color: blue; background-color: white;"
                                  "width: 150px; height: 35px;}"
                                  ));

    QPushButton *pButtonOk = box->addButton("Ok", QMessageBox::AcceptRole);
    pButtonOk->setStyleSheet("QPushButton{color: rgb(255, 255, 255); background-color: rgba(0, 180, 0, 180); border-style: outset; border-width: 2px; border-radius: 10px; border-color: beige; font: bold 14px; min-width: 10em; padding: 6px;}"
                             "QPushButton::pressed {color: rgb(255, 255, 255); background-color: rgba(0, 150, 0, 130); border-style: inset;}");
    pButtonOk->setShortcut(Qt::Key_Enter);
    box->exec();

    delete box;
}

void ChooseGhost::on_BackButton_clicked()
{
    this->close();
    delete this;
}
