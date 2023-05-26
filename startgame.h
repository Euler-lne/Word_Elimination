#ifndef STARTGAME_H
#define STARTGAME_H

#include <QWidget>
#include "answer.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>
#include <QTime>
#include <QKeyEvent>

enum GameType{ENDLESS,CHANLLENGE};

namespace Ui {
class StartGame;
}

class StartGame : public QWidget
{
    Q_OBJECT

public:
    explicit StartGame(QWidget *parent = 0);
    ~StartGame();
    void InitStartGame(my_answer::Answer*);

public slots:
    void ClickBackMenuBtn();
    void ClickConfirmBtn();


signals:
    void BackToMenu();

private:
    Ui::StartGame *ui;    
    my_answer::Answer *answer;
    QString expectedWord;
    QJsonArray levelWords;
    QJsonObject levelData;
    QTime startTime;
    GameType gameType;
    int levelNum;
    int leftWord;
    int timerID;
    int challengerTimerID;
    int *randArray;
    bool canPressEnter;
    float levelTime;

    void InitConnect();
    void UpdateUI();
    void SetWord(int _index);
    void SetRandArray(int _len);
    void WordTimeOut();
    void timerEvent(QTimerEvent* t);
    void keyPressEvent(QKeyEvent *event);
    void SelectGameType();
    int SetLevel(int _level);

};

#endif // STARTGAME_H
