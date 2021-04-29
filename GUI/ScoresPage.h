#ifndef SCORESPAGE_H
#define SCORESPAGE_H

#include <QMainWindow>

namespace Ui {
class ScoresPage;
}

class ScoresPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit ScoresPage(QWidget *parent = nullptr);
    ~ScoresPage();

private:
    void InitUi();

    void InitData();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ScoresPage *ui;
};

#endif // SCORESPAGE_H
