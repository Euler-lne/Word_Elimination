#include "startgame.h"
#include "ui_startgame.h"
#include "savemanager.h"
#include <QDebug>
#include <ctime>
#include <cstdlib>

StartGame::StartGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartGame)
{
    ui->setupUi(this);
    answer = NULL;
    randArray = NULL;
    InitConnect();
    srand((unsigned)time(0));
}

StartGame::~StartGame()
{
    delete ui;
    if(randArray != NULL)
        delete []randArray;
    randArray = NULL;
}
void StartGame::InitConnect()
{
    connect(ui->backBtn,&QPushButton::clicked,this,&StartGame::ClickBackMenuBtn);
    connect(ui->confrimBtn,&QPushButton::clicked,this,&StartGame::ClickConfirmBtn);
}

/// 从选择关卡窗口离开，需要保存数据
void StartGame::ClickBackMenuBtn()
{
    answer->UpdateData();
    emit BackToMenu();
}

/// 来到此窗口
void StartGame::InitStartGame(my_answer::Answer* _answer)
{
    answer = _answer;
    UpdateUI();
    int key;
    levelNum = 1;
    key = SetLevel(levelNum);
    if(key == SaveManager::NOT_EXIST)
        qDebug() << "关卡不存在";
}

void StartGame::UpdateUI()
{
    ui->accountLab->setText(answer->GetName());
    ui->gradeLab->setText(QString::number(answer->GetGrade()));
    ui->expLab->setText(QString::number(answer->GetEXP())+"/"+QString::number(answer->GetMax()));
}

int StartGame::SetLevel(int _level)
{
    int key = SaveManager::LoadLevel(_level, levelData);
    if(key == SaveManager::NOT_EXIST || key == SaveManager::ERROR)
        return key;
    leftWord = levelData.value("num").toInt();
    levelWords = levelData.value("words").toArray();
    QString tempString = "第" + QString::number(_level) + "关";
    ui->levelNum->setText(tempString);
    ui->confrimBtn->setText("确定");
    int len = levelWords.size();
    if(randArray != NULL)
    {
        delete []randArray;
        randArray = NULL;
    }
    randArray = new int[len];
    SetRandArray(len);
    SetWord(randArray[leftWord-1]);
    return key;
}

void StartGame::SetWord(int _index)
{
    expectedWord = levelWords.at(randArray[_index]).toString();
    QString tempString = "该关卡剩余单词：" + QString::number(leftWord);
    ui->leftWord->setText(tempString);
    ui->expected->setText(expectedWord);
    ui->playInput->setEnabled(false);
    ui->playInput->setText("");
    ui->confrimBtn->setEnabled(false);
    int len = expectedWord.length();
    levelTime =  5.5 * ((len / 5.0 + 1)/3) * (4.0/(levelNum/10.0 + 1)); //每一个单词的时间都不一样
    startTime = QTime::currentTime();
    timerID = startTimer(100);
}

void StartGame::SetRandArray(int _len)
{
    for(int i=0;i<_len;i++)
        randArray[i] = i;
    // 因为不能对0去模长，要避开0，初始化为len-1
    for(int i = _len - 1;i >= 1;i--)
    {
        int temp = randArray[i];
        int tempIndex = rand() % i;
        randArray[i] = randArray[tempIndex];
        randArray[tempIndex] = temp;
    }
}

void StartGame::WordTimeOut()
{
    ui->expected->setText("");
    ui->playInput->setEnabled(true);
    ui->confrimBtn->setEnabled(true);
}

void StartGame::ClickConfirmBtn()
{
    if(leftWord == 0)   //这里要放到外面来判断
    {
        SetLevel(levelNum);
    }
    else
    {
        if(expectedWord == ui->playInput->text())
        {
            //正确
            leftWord--;
            answer->UpdateEXP(levelNum,expectedWord.length());
            if(leftWord == 0)   //这个只是改变了名称，需要再按一次，再按一次的时候leftWord已经为0
            {
                //最后一个正确下一关
                ui->confrimBtn->setText("下一关");//一共只有40关
                QString tempString = "该关卡剩余单词：" + QString::number(leftWord);
                ui->playInput->setEnabled(false);
                ui->playInput->setText("");
                ui->leftWord->setText(tempString);
                answer->UpdateEXP(levelNum,-1);
                levelNum ++;
                //玩家相关属性改变，因为当前的关卡数已经增加，所以只有当前关卡数大于玩家自生关数才会增加
                if(levelNum > answer->GetLevelNum())
                    answer->IncreaseLevelNum();
                answer->UpdateData();
            }
            else
            {
                SetWord(randArray[leftWord-1]);
            }
        }
        else
        {
            SetWord(randArray[leftWord-1]);
        }
    }
    UpdateUI();
}
void StartGame::timerEvent(QTimerEvent *t)
{
    if(t->timerId() == timerID)
    {
        QTime currentTime = QTime::currentTime();
        int tempInt = 100 - ((startTime.msecsTo(currentTime) / (levelTime * 1000) \
                             + startTime.secsTo(currentTime)/levelTime)*100);
        if(tempInt <= 0)
        {
            tempInt = 0;
            WordTimeOut();
            killTimer(timerID);
        }
        if(tempInt >= 100)
        {
            tempInt = 100;
        }
        ui->progressBar->setValue(tempInt);
    }
}
