#include "answer.h"
#include "savemanager.h"
using namespace my_answer;

Answer::Answer(QString _name) : Player(_name)
{
    playerType = PlayerType::Answer;
    LoadData();
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
