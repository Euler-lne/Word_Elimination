#include "maker.h"
#include "savemanager.h"

Maker::Maker(QString _name) : Player(_name)
{
    playerType = PlayerType::Maker;
    LoadData();
}
void Maker::UpdateData()
{
    data[SaveManager::LEVEL_NUM] = levelNum;
    data[SaveManager::GRADE] = grade;
    SaveManager::SavePlayerMaker(name, data);
}
void Maker::LoadData()
{
    SaveManager::LoadPlayerMaker(name, data);
    grade =  data.value(SaveManager::GRADE).toInt();
    levelNum = data.value(SaveManager::LEVEL_NUM).toInt();
}
