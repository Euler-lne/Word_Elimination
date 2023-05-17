#include "maker.h"
#include "savemanager.h"
using namespace my_maker;

Maker::Maker(QString _name) : Player(_name)
{
    playerType = PlayerType::Maker;
    LoadData();
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
