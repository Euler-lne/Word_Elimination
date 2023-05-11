#ifndef ANSWERWINDOW_H
#define ANSWERWINDOW_H

class SelectLevel;

#include <QWidget>
#include <QJsonObject>
#include <QString>
#include "answer.h"
#include "selectlevel.h"

namespace Ui {
class AnswerWindow;
}

class AnswerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AnswerWindow(QWidget *parent = 0);
    ~AnswerWindow();
    void SetPlayerName(QString);

private:
    Ui::AnswerWindow *ui;
    void InitConnect();
    QString playerName;
    my_answer::Answer *answer;
    SelectLevel *selectLevel;

public slots:
    void ClickStartBtn();
    void ClickRankBtn();
    void ClickAccountBtn();
    void SeletLevelToThis();
};

#endif // ANSWERWINDOW_H
