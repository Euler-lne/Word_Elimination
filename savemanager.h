#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H
#include <QString>
#include <QJsonObject>

class SaveManager
{
public:
    SaveManager();
    static int LoadUser(const QString,const QString,const int);
    static int LoadUserType(const QString _name, int & _type);
    static int SaveUser(const QString,const QString,const int);
    static int LoadPlayerMaker(const QString,QJsonObject &);
    static int LoadPlayerAnswer(const QString,QJsonObject &);
    static int LoadLevel(const int, QJsonObject &);
    static int LoadAllPlayerName(int &_playerNum,QString * _playerArry);
    static int SavePlayerMaker(const QString,const QJsonObject);
    static int SavePlayerAnswer(const QString, const QJsonObject);
    static int AddWord(QString);
    static int RemoveUser(const QString);
    static int RemovePlayer(const QString);
    static const QString PATH;
    static const int ERROR;
    static const int TYPE_ERROR;
    static const int PASSWORD_ERROR;
    static const int OK;
    static const int EXIST;
    static const int NOT_EXIST;
    static const int CHANGE_TYPE;
    static const QString LEVEL_NUM;
    static const QString GRADE;
    static const QString EXP;
    static const QString ANSWER;
    static const QString MAKER;

};

#endif // SAVEMANAGER_H
