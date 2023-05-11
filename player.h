#ifndef PLAYER_H
#define PLAYER_H
#include <QString>

enum PlayerType{Answer,Maker};

class Player
{
public:
    Player(QString);

protected:
    PlayerType playerType;
    QString name;
    int levelNum;
    int grade;
};

#endif // PLAYER_H
