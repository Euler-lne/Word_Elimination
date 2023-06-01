#include "answer.h"
#include "savemanager.h"
#include "math.h"
using namespace my_answer;

Answer::Answer(QString _name) : Player(_name)
{
    playerType = PlayerType::Answer;
    LoadData();
    max = 10 * pow(2,grade/5 +2);
}

void Answer::UpdateData()
{
    data[SaveManager::LEVEL_NUM] = levelNum;
    data[SaveManager::GRADE] = grade;
    data[SaveManager::EXP] = exp;
    SaveManager::SavePlayerAnswer(name,data);
}
void Answer::LoadData()
{
    SaveManager::LoadPlayerAnswer(name, data);
    exp = data.value(SaveManager::EXP).toInt();
    grade =  data.value(SaveManager::GRADE).toInt();
    levelNum = data.value(SaveManager::LEVEL_NUM).toInt();
}

void Answer::UptateEXP(int _level, int _length)
{
    max = 10 * pow(2,grade/5 +2);
    if(_length == -1)
    {
        if(_level <= levelNum)
            exp = exp + 5 * _level;
        else
            exp = exp + 10 * _level;
    }
    else
    {
        exp = exp + 5 * _length;
    }
    if(exp >= max)
    {
        exp = exp - max;
        UpdateGrade(1);
    }
}

void Answer::UptateEXP(int _exp)
{
    max = 10 * pow(2,grade/5 +2);
    if(_exp>0)
    {
        exp+=_exp;
        if(exp >= max)
        {
            exp -= max;
            UpdateGrade(1);
        }
    }
    else
    {
        exp -= _exp;
        while(exp < 0)
        {
            UpdateGrade(-1);
            max = 10 * pow(2,grade/5 +2);
            exp = max + exp;
            //不够减的情况
            if(grade == 0 && exp <0)
            {
                exp = 0;
                break;
            }
        }
    }
}
