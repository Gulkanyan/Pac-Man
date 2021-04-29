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
    Ui::ScoresPage *ui;
};

#endif // SCORESPAGE_H
