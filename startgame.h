#ifndef STARTGAME_H
#define STARTGAME_H

#include <QWidget>
#include "answer.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>

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
    QString playerName;
    my_answer::Answer *answer;
    QJsonObject levelData;
    QTimer * timer;
    int levelNum;
    float levelTime;
    QJsonArray levelWords;

    void InitConnect();
    void UpdateUI();
    int SetLevel(int _level);
    int getRand(int min, int max) {
       return ( rand() % (max - min + 1) ) + min ;}
    // 左闭右闭区间

};

#endif // STARTGAME_H
