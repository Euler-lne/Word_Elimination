#ifndef PLAYER_H
#define PLAYER_H
#include <QString>
#include <QJsonObject>

enum PlayerType{Answer,Maker};

class Player
{
public:
    Player(QString);
    QString GetName(){return name;}
    int GetLevelNum(){return levelNum;}
    int GetGrade(){return grade;}
    int GetEXP(){return exp;}
    int GetMax(){return max;}
    void IncreaseLevelNum() {levelNum++;}


protected:
    PlayerType playerType;
    QString name;
    QJsonObject data;
    int levelNum;
    int exp;
    int grade;
    int max;

    void UpdateGrade(int _num){
        grade += _num;
        if(grade <0)
            grade = 0;
    }




};

#endif // PLAYER_H
