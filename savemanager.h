#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H
#include <QString>


class SaveManager
{
public:
    SaveManager();
    static int LoadUser(const QString,const QString,const int);
    static int SetUser(const QString,const QString,const int);
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
