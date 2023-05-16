#ifndef STARTGAME_H
#define STARTGAME_H

#include <QWidget>
#include "answer.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>
#include <QTime>

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
    void ClickConfirmBtn();


signals:
    void BackToMenu();

private:
    Ui::StartGame *ui;    
    my_answer::Answer *answer;
    QString playerName;
    QString expectedWord;
    QJsonArray levelWords;
    QJsonObject levelData;
    QTime startTime;
    int levelNum;
    int leftWord;
    int timerID;
    int *randArray;
    float levelTime;

    void InitConnect();
    void UpdateUI();
    void SetWord(int _index);
    void SetRandArray(int _len);
    void WordTimeOut();
    void timerEvent(QTimerEvent* t);
    int SetLevel(int _level);

};

#endif // STARTGAME_H
