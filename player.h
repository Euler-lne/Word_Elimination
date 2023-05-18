#ifndef PLAYER_H
#define PLAYER_H
#include <QString>
#include <QJsonObject>

enum PlayerType{Answer,Maker};

class Player
{
public:
    Player(QString);
<<<<<<< HEAD
    int GetLevelNum(){ return levelNum;}
    int GetGrade(){ return grade;}
=======
    QString GetName(){return name;}
    int GetLevelNum(){return levelNum;}
    int GetGrade(){return grade;}
    int GetEXP(){return exp;}
    void IncreaseLevelNum() {levelNum++;}
>>>>>>> 3152c913f1004170e87fa93e11922719e7edf60d


protected:
    PlayerType playerType;
    QString name;
    QJsonObject data;
    int levelNum;
    int exp;
    int grade;




};

#endif // PLAYER_H
