#ifndef PLAYER_H
#define PLAYER_H
#include <QString>
#include <QJsonObject>

enum PlayerType{Answer,Maker};

class Player
{
public:
    Player(QString);
    int GetLevelNum(){return levelNum;}
    int GetGrade(){return grade;}
    void IncreaseLevelNum() {levelNum++;}

protected:
    PlayerType playerType;
    QString name;
    QJsonObject data;
    int levelNum;
    int grade;


};

#endif // PLAYER_H
