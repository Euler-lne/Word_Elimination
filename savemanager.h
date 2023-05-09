#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H
#include <QString>


class SaveManager
{
public:
    SaveManager();
    static int LoadUser(QString,QString,int);
    static int SetUser(QString,QString,int);
    static const QString PATH;
    static const int ERROR;
    static const int TYPE_ERROR;
    static const int PASSWORD_ERROR;
    static const int RIGHT;
    static const int EXIST;

};

#endif // SAVEMANAGER_H
