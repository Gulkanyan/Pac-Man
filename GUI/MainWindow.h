#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSound>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_play_clicked();

    void on_about_clicked();

    void on_settings_clicked();

    void on_help_clicked();

    void on_soresPageBtn_clicked();

private:
    void InitPage();

    void InitStarter() const;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
