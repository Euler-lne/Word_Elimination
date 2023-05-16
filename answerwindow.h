#ifndef ANSWERWINDOW_H
#define ANSWERWINDOW_H

class StartGame;

#include <QWidget>
#include <QJsonObject>
#include <QString>
#include "startgame.h"

namespace Ui {
class AnswerWindow;
}

class AnswerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AnswerWindow(QWidget *parent = 0);
    ~AnswerWindow();
    void SetPlayerName(QString _name){playerName = _name;}

private:
    Ui::AnswerWindow *ui;
    void InitConnect();
    QString playerName;
    StartGame *startGame;

private slots:
    void ClickStartBtn();
    void ClickRankBtn();
    void ClickAccountBtn();
    void StartGameToThis();
};

#endif // ANSWERWINDOW_H
