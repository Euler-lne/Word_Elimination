#ifndef PLAYER_H
#define PLAYER_H
#include <QString>

enum PlayerType{Answer,Maker};

class Player
{
public:
    Player(QString);
    void SetLevelNum(int _num){ levelNum = _num;}
    void SetGrade(int _grade){grade = _grade;}


protected:
    PlayerType playerType;
    QString name;
    int levelNum;
    int grade;
};

#endif // PLAYER_H
