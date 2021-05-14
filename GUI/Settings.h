#ifndef SETTINGS_H
#define SETTINGS_H

#include <QMainWindow>

namespace Ui {
class Settings;
}

class Settings : public QMainWindow
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private:
    void InitUi();

private slots:
    void on_pushButton_clicked();

    void on_turnOn_clicked();

    void on_turnOff_clicked();

    void on_easy_clicked();

    void on_normal_clicked();

    void on_Hard_clicked();

    void on_LangComboBox_currentIndexChanged(int index);

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_H
