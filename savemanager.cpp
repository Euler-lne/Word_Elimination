#include "savemanager.h"
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
const QString SaveManager::LEVEL_NUM = "Level Num";
const QString SaveManager::GRADE = "Grade";
const QString SaveManager::EXP = "EXP";
const QString SaveManager::ANSWER = "Answer";
const QString SaveManager::MAKER = "Maker";
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

int SaveManager::LoadUserType(const QString _name, int &_type)
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
        _type = object.value(_name).toArray().at(1).toInt();
        return OK;
    }
    else {
        return NOT_EXIST;
    }

}

int SaveManager::SaveUser(const QString _name, const QString _password, const int _type)
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
    RemovePlayer(_name);
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
    {
        object.remove(_name);
    }
    else
    {
        doc.setObject(object);
        file2.write(doc.toJson());
        file2.close();
        return NOT_EXIST;
    }
    doc.setObject(object);
    file2.write(doc.toJson());
    file2.close();
    return OK;
}

int SaveManager::RemovePlayer(const QString _name)
{
    QString path = PATH + "/data/player.json";
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
        doc.setObject(object);
        file2.write(doc.toJson());
        file2.close();
        return NOT_EXIST;
    }
    doc.setObject(object);
    file2.write(doc.toJson());
    file2.close();
    return OK;
}

int SaveManager::LoadPlayerAnswer(const QString _name, QJsonObject &_answerData)
{
    QString path = PATH + "/data/player.json";
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
        QJsonObject player = object.value(_name).toObject();
        QJsonObject answer = player.value(ANSWER).toObject();
        _answerData = answer;
    }
    else
    {
        _answerData.insert(LEVEL_NUM, 1);
        _answerData.insert(GRADE, 0);
        _answerData.insert(EXP, 0);
        SavePlayerAnswer(_name, _answerData);
    }
    return OK;
}
//也可以返回一个JsonObject，这样可以减少参数
int SaveManager::LoadPlayerMaker(const QString _name, QJsonObject &_makerData)
{
    QString path = PATH + "/data/player.json";
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
        QJsonObject player = object.value(_name).toObject();
        QJsonObject maker = player.value(MAKER).toObject();
        _makerData = maker;
    }
    else
    {
        _makerData.insert(LEVEL_NUM, 0);
        _makerData.insert(GRADE, 0);
        _makerData.insert(EXP,0);
        SavePlayerMaker(_name, _makerData);
    }
    return OK;
}

int SaveManager::LoadLevel(const int _level, QJsonObject & _levelData)
{
    QString path = PATH + "/data/level.json";
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
    QString levelString = QString::number(_level);
    if(object.contains(levelString))
    {
        QJsonObject level = object.value(levelString).toObject();
        _levelData = level;
    }
    else
    {
        return NOT_EXIST;
    }
    return OK;
}

int SaveManager::SavePlayerAnswer(const QString _name, const QJsonObject _answerData)
{
    QString path = PATH + "/data/player.json";
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
        QJsonObject player = object.value(_name).toObject();
        QJsonObject answer = player.value(ANSWER).toObject();
        answer[LEVEL_NUM] = _answerData[LEVEL_NUM];
        answer[GRADE] = _answerData[GRADE];
        answer[EXP] = _answerData[EXP];
        player[ANSWER] = answer;
        object[_name] = player;
    }
    else
    {
        QJsonObject player;
        QJsonObject answer,maker;
        answer = _answerData;
        maker.insert(LEVEL_NUM,0);
        maker.insert(GRADE,0);
        maker.insert(EXP,0);
        player.insert(ANSWER,answer);
        player.insert(MAKER,maker);
        object.insert(_name,player);
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
    return OK;
}

int SaveManager::SavePlayerMaker(const QString _name, const QJsonObject _makerData)
{
    QString path = PATH + "/data/player.json";
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
        QJsonObject player = object.value(_name).toObject();
        QJsonObject maker = player.value(MAKER).toObject();
        maker[LEVEL_NUM] = _makerData[LEVEL_NUM];
        maker[GRADE] = _makerData[GRADE];
        maker[EXP] = _makerData[EXP];
        player[MAKER] = maker;
        object[_name] = player;
    }
    else
    {
        QJsonObject player;
        QJsonObject answer,maker;
        maker = _makerData;
        answer.insert(LEVEL_NUM,1);
        answer.insert(GRADE,0);
        answer.insert(EXP,0);
        player.insert(ANSWER,answer);
        player.insert(MAKER,maker);
        object.insert(_name,player);
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
    return OK;
}

int SaveManager::AddWord(QString _word)
{
    AddWordArry(_word);
    QString path = PATH + "/data/level.json";
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
    int len = _word.length();
    if(len/5 >= 3)
        len = 15;
    //一共分出40关
    for(int i = len / 5 * 10 + 1; i <= len / 5 * 10 + 10;i++)
    {
        QJsonObject level;
        QJsonArray arry;
        QString iString = QString::number(i);
        if(object.contains(iString))
        {
            level = object.value(iString).toObject();
            arry = level["words"].toArray();
            if(arry.contains(_word))
                return EXIST;
            arry.append(_word);
            level["words"] = arry;
            object[iString] = level;
        }
        else
        {
            int tempNum = 0;
            switch (i/5)
            {
            case 0:
                tempNum = 3;
                break;
            case 1:
                tempNum = 5;
                break;
            case 2:
                tempNum = 7;
                break;
            case 3:
                tempNum = 9;
                break;
            case 4:
                tempNum = 11;
                break;
            case 5:
                tempNum = 13;
                break;
            case 6:
                tempNum = 15;
                break;
            case 7:
                tempNum = 17;
                break;
            default:
                tempNum = 20;
                break;
            }
            switch (i) {
            case 1:
            case 2:
            case 3:
                tempNum = 1;
                break;
            default:
                break;
            }
            QJsonArray words;
            words.append(_word);
            level["num"] = tempNum;
            level["words"] = words;
            object.insert(iString, level);
        }
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
    return OK;
}

QString SaveManager::GetWord()
{
    QString path = PATH + "/data/word.json";
    QFile file1(path);
    if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"打开文件失败";
        return "";
    }
    QTextStream in(&file1);
    QString jsonString = in.readAll();
    file1.close();
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonArray arry = doc.array();
    return "";
}

void SaveManager::AddWordArry(const QString _word)
{
    QString path = PATH + "/data/word.json";
    QFile file1(path);
    if(!file1.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"打开文件失败";
        return;
    }
    QTextStream in(&file1);
    QString jsonString = in.readAll();
    file1.close();
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonArray arry = doc.array();
    if(!arry.contains(_word))
    {
        arry.append(_word);
    }
    doc.setArray(arry);
    QFile file2(path);
    if(!file2.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<<"打开文件失败";
        return;
    }
    file2.write(doc.toJson());
    file2.close();
}

int SaveManager::LoadAllPlayerName(QString *_playerArry)
{
    QString path = PATH + "/data/player.json";
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
    QJsonObject::Iterator it;
    int i;
    for(it=object.begin(),i=0;it!=object.end();it++,i++)
    {
        _playerArry[i]=it.key();
    }
    return OK;
}

int SaveManager::LoadAllPlayerNum(int &_playerNum)
{
    QString path = PATH + "/data/player.json";
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
    _playerNum = object.length();
    return OK;
}
