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

protected:
    PlayerType playerType;
    QString name;
    int levelNum;
    int grade;
    QJsonObject data;
};

#endif // PLAYER_H
