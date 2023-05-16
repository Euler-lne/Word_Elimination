#ifndef STARTGAME_H
#define STARTGAME_H

#include <QWidget>
#include "answer.h"
#include <QJsonObject>

namespace Ui {
class StartGame;
}

class StartGame : public QWidget
{
    Q_OBJECT

public:
    explicit StartGame(QWidget *parent = 0);
    ~StartGame();
    void InitStartGame(QString);

public slots:
    void ClickBackMenuBtn();

signals:
    void BackToMenu();

private:
    Ui::StartGame *ui;
    void InitConnect();
    void UpdateUI();
    QString playerName;
    my_answer::Answer *answer;
    QJsonObject levelData;

};

#endif // STARTGAME_H
