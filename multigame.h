#ifndef MULTIGAME_H
#define MULTIGAME_H

#include <QWidget>
#include <QString>
#include <QTime>
#include <QTimer>
#include <QKeyEvent>

namespace Ui {
class MultiGame;
}

class MultiGame : public QWidget
{
    Q_OBJECT

public:
    explicit MultiGame(QWidget *parent = 0);
    ~MultiGame();
    void UpdatePlayer1(QString _name,int _lastWord);
    void UpdatePlayer2(QString _name,int _lastWord);
    void SetWords(QString _words){
        words = _words;
        wordNum = 10;
        UpdateWord();
    }

private:
    Ui::MultiGame *ui;
    QTime startTime;
    QString words;
    QString expectedWord;

    bool canPressEnter;
    int timerID;
    int wordNum;
    float levelTime;

    void ClickConfirmBtn();
    void WordTimeOut();
    void UpdateWord();
    void timerEvent(QTimerEvent* t);
    void keyPressEvent(QKeyEvent *event);

signals:
    void WordRight(QString _name,int _wordNum);
    void EndOfAnswer();
};

#endif // MULTIGAME_H
