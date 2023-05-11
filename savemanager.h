#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H
#include <QString>

class Answer;
class Maker;

class SaveManager
{
public:
    SaveManager();
    static int LoadUser(const QString,const QString,const int);
    static int SaveUser(const QString,const QString,const int);
    static int LoadPlayerMaker(Maker *);
    static int LoadPlayerAnswer(Answer *);
    static int SavePlayerMaker(const Maker *);
    static int SavePlayerAnswer(const Answer *);
    static int RemoveUser(const QString);
    static const QString PATH;
    static const int ERROR;
    static const int TYPE_ERROR;
    static const int PASSWORD_ERROR;
    static const int OK;
    static const int EXIST;
    static const int NOT_EXIST;
    static const int CHANGE_TYPE;

};

#endif // SAVEMANAGER_H
