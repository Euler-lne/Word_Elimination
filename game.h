#ifndef GAME_H
#define GAME_H


#include <QWidget>
#include <QJsonObject>
#include <QString>
#include "answer.h"

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = 0);
    void SetPlayer(QString);
    ~Game();

private:
    Ui::Game *ui;
    void InitConnect();
    QString playerName;
    my_answer::Answer *answer;
    QJsonObject answerData;

public slots:
    void ClickStartBtn();
    void ClickRankBtn();
    void ClickAccountBtn();
};

#endif // GAME_H
