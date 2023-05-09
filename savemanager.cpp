#include "savemanager.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QFile>

const int SaveManager::ERROR = -1;
const int SaveManager::TYPE_ERROR = 0;
const int SaveManager::OK = 1;
const int SaveManager::EXIST = 2;
const int SaveManager::PASSWORD_ERROR = 3;
const int SaveManager::NOT_EXIST = 4;
const int SaveManager::CHANGE_TYPE = 5;
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
int SaveManager::LoadUser(const QString _name, const QString _password, const int _type)
{
    QString path = PATH + "/data/user.json";
    QFile file1(path);
    if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"打开文件失败";
        return ERROR;
    }
    QTextStream in(&file1);
    QString jsonString = in.readAll();
    file1.close();
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject object = doc.object();
    if(object.contains(_name))
    {
        QJsonArray arry = object.value(_name).toArray();
        if(arry.at(0).toString() == _password && (arry.at(1).toInt() == _type || arry.at(1).toInt()==2))
            return OK;
        else if(arry.at(0).toString() == _password)
            return TYPE_ERROR;
    }
    return PASSWORD_ERROR;
}

int SaveManager::SetUser(const QString _name, const QString _password, const int _type)
{
    bool key = false;
    QString path = PATH + "/data/user.json";
    QFile file1(path);
    if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"打开文件失败";
        return ERROR;
    }
    QTextStream in(&file1);
    QString jsonString = in.readAll();
    file1.close();
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject object = doc.object();
    if(object.contains(_name))
    {
        QJsonArray arry = object.value(_name).toArray();
        if(arry.at(0).toString() == _password && arry.at(1).toInt() != _type)
        {
            if(arry.at(1).toInt() == 2) //要降低权限
            {
                arry.removeAt(1);
                arry.append(_type);
            }
            else                        //两个不一样，一个是0，一个是1，而且没有升级权限
            {
                arry.removeAt(1);
                arry.append(2);
            }
            object[_name] = arry;
            key = true;
        }
        else if(arry.at(0).toString() == _password)
        {
            //都正确
            return EXIST;
        }
        else
        {
            //账号存在密码错误
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
    QFile file2(path);
    if(!file2.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<<"打开文件失败";
        return ERROR;
    }
    file2.write(doc.toJson());
    file2.close();
    if(key)
        return CHANGE_TYPE;
    else
        return OK;
}

int SaveManager::RemoveUser(const QString _name)
{
    QString path = PATH + "/data/user.json";
    QFile file1(path);
    if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"打开文件失败";
        return ERROR;
    }
    QTextStream in(&file1);
    QString jsonString = in.readAll();
    file1.close();
    QFile file2(path);
    if(!file2.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<<"打开文件失败";
        return ERROR;
    }
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject object = doc.object();
    if(object.contains(_name))
        object.remove(_name);
    else
    {
        file2.close();
        return NOT_EXIST;
    }
    doc.setObject(object);
    file2.write(doc.toJson());
    file2.close();
    return OK;
}

