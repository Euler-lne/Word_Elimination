#include "maker.h"
#include "savemanager.h"
using namespace my_maker;

Maker::Maker(QString _name) : Player(_name)
{
    playerType = PlayerType::Maker;
    LoadData();
    max = 10 * pow(2,grade/5 +2);
}
void Maker::UpdateData()
{
    data[SaveManager::LEVEL_NUM] = levelNum;
    data[SaveManager::GRADE] = grade;
    data[SaveManager::EXP] = exp;
    SaveManager::SavePlayerMaker(name, data);
}
void Maker::LoadData()
{
    SaveManager::LoadPlayerMaker(name, data);
    exp = data.value(SaveManager::EXP).toInt();
    grade =  data.value(SaveManager::GRADE).toInt();
    levelNum = data.value(SaveManager::LEVEL_NUM).toInt();
}

void Maker::UpdateEXP(int _length)
{
    max = 10 * pow(2,grade/5 +2);
    exp = exp + 10 * _length * (levelNum*0.5 +1);
    if(exp >= max)
    {
        exp = exp - max;
        UpdateGrade(1);
    }
    UpdateData();
}
