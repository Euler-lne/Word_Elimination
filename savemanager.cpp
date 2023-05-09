#include "savemanager.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QFile>

const int SaveManager::ERROR = -1;
const int SaveManager::TYPE_ERROR = 0;
const int SaveManager::RIGHT = 1;
const int SaveManager::EXIST = 2;
const int SaveManager::PASSWORD_ERROR = 3;
const QString SaveManager::PATH = "../Word_Elimination";
SaveManager::SaveManager()
{
}
///
/// \brief SaveManager::LoadUser
/// \param _name
/// \param _password
/// \param _type
/// \return 0：用户名或者密码错误；1：正确且类型正确；2：正确且类型错误
///
int SaveManager::LoadUser(QString _name, QString _password, int _type)
{
    QString path = PATH + "/data/user.json";
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"打开文件失败";
        return ERROR;
    }
    QTextStream in(&file);
    QString jsonString = in.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject object = doc.object();
    if(object.contains(_name))
    {
        QJsonArray arry = object.value(_name).toArray();
        if(arry.at(0).toString() == _password && (arry.at(1).toInt() == _type || arry.at(1).toInt()==2))
            return RIGHT;
        else if(arry.at(0).toString() == _password)
            return TYPE_ERROR;
    }
    return PASSWORD_ERROR;
}

int SaveManager::SetUser(QString _name, QString _password, int _type)
{
    QString path = PATH + "/data/user.json";
    qDebug() << path;
    QFile file(path);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug()<<"打开文件失败";
        return ERROR;
    }
    QTextStream in(&file);
    QString jsonString = in.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject object = doc.object();
    if(object.contains(_name))
    {
        QJsonArray arry = object.value(_name).toArray();
        if(arry.at(0).toString() == _password && arry.at(1).toInt() != _type && arry.at(1).toInt()!=2)
        {
            arry.at(1) = 2;
            object.value(_name) = arry;
        }
        else if(arry.at(0).toString() == _password)
        {
            //都正确
            file.close();
            return EXIST;
        }
        else
        {
            //账号存在密码错误
            file.close();
            return PASSWORD_ERROR;
        }
    }
    else
    {
        QJsonArray arry;
        arry.append(_password);
        arry.append(_type);
        object.insert(_name,arry);
    }
    doc.setObject(object);
    in << doc.toJson();
    file.close();
    return RIGHT;
}

