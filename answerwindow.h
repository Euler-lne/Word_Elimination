#ifndef ANSWERWINDOW_H
#define ANSWERWINDOW_H

class StartGame;

#include <QWidget>
#include <QJsonObject>
#include <QString>
#include "answer.h"
#include "startgame.h"
#include "accountwindow.h"
class AccountWindow;

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
    my_answer::Answer *answer;

private slots:
    void ClickStartBtn();
    void ClickRankBtn();
    void ClickAccountBtn();
    void StartGameToThis();
    void AccountWindowToThis();
    void ClickLogin();

signals:
    void BackToLogin();
};

#endif // ANSWERWINDOW_H
