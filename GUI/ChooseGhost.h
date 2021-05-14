#ifndef CHOOSEGHOST_H
#define CHOOSEGHOST_H

#include <QMainWindow>

namespace Ui {
class ChooseGhost;
}

class ChooseGhost : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChooseGhost(QWidget *parent = nullptr);
    ~ChooseGhost();

private:
    void ShowMessageBox();

    void InitUi();

private slots:
    void on_pushButton_clicked();

    void on_BackButton_clicked();

signals:
    void StartMultiplayer();

private:
    Ui::ChooseGhost *ui;
};

#endif // CHOOSEGHOST_H
