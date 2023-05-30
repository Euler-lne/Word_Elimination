#ifndef ANSWERWINDOW_H
#define ANSWERWINDOW_H

class StartGame;
class AccountWindow;
class RankWindow;

#include <QWidget>
#include <QJsonObject>
#include <QString>
#include "answer.h"
#include "startgame.h"
#include "accountwindow.h"
#include "rankwindow.h"
#include "multiplayerwindow.h"

namespace Ui {
class AnswerWindow;
}

class AnswerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AnswerWindow(QWidget *parent = 0);
    ~AnswerWindow();
    void InitAnswerWindow(QString _name);

private:
    Ui::AnswerWindow *ui;
    void InitConnect();
    QString playerName;
    StartGame *startGame;
    AccountWindow *accountWindow;
    RankWindow *rankWindow;
    MultiplayerWindow *multiplayerWindow;
    my_answer::Answer *answer;

private slots:
    void ClickStartBtn();
    void ClickRankBtn();
    void ClickAccountBtn();
    void StartGameToThis();
    void AccountWindowToThis();
    void RankWindowToThis();
    void ClickLogin();
    void ClickMultiplayerBtn();
    void MultiplayerWindowToThis();

signals:
    void BackToLogin();
};

#endif // ANSWERWINDOW_H
