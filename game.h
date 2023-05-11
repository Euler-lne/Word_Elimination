#ifndef GAME_H
#define GAME_H

class Maker;
class Answer;

#include <QWidget>
#include <QString>

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
    Answer *answer;
    Maker *maker;

public slots:
    void ClickStartBtn();
    void ClickRankBtn();
    void ClickAccountBtn();
};

#endif // GAME_H
