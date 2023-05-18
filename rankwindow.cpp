#include "rankwindow.h"
#include "ui_rankwindow.h"
#include "savemanager.h"
#include <QDebug>

RankWindow::RankWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RankWindow)
{
    ui->setupUi(this);
    playerArray = NULL;
    InitConnect();
}

RankWindow::~RankWindow()
{
    delete ui;
    if(playerArray != NULL)
        delete []playerArray;
    playerArray = NULL;
}

void RankWindow::InitConnect()
{
    connect(ui->backMenuBtn,&QPushButton::clicked,this,&RankWindow::ClickBackMenuBtn);
    connect(ui->answerRadio,SIGNAL(toggled(bool)),this,SLOT(CheckSlotAnswer(bool)));
    connect(ui->makerRadio,SIGNAL(toggled(bool)),this,SLOT(CheckSlotMaker(bool)));
}

void RankWindow::ClickBackMenuBtn()
{
    emit BackToMenu();
}
void RankWindow::InitRankWindow(bool _isAnswer)
{   
    isAnswer = _isAnswer;
    if(playerArray != NULL)
        delete []playerArray;
    playerArray = NULL;
    playerNum = 0;
    SaveManager::LoadAllPlayerNum(playerNum);
    playerArray = new QString[playerNum];
    SaveManager::LoadAllPlayerName(playerArray);
    ui->answerRadio->setChecked(isAnswer);
    ui->makerRadio->setChecked(!isAnswer);
    UpdateUI();
}

void RankWindow::UpdateUI()
{
    if(isAnswer)
    {
        ui->rankLab->setText("闯关者排名");
        rankNum = 0;
        for(int i=0;i<playerNum;i++)
        {
            int type;
            SaveManager::LoadUserType(playerArray[i],type);
            if(type == 1 || type == 2)
            {
                if(rankNum != i)
                {
                    QString tempString = playerArray[i];
                    playerArray[i] = playerArray[rankNum];
                    playerArray[rankNum] = tempString;
                }
                rankNum ++;
            }
        }
        SortPlayerByGrade();
    }
    else
    {
        ui->rankLab->setText("出题者排名");
        rankNum = 0;
        for(int i=0;i<playerNum;i++)
        {
            int type;
            SaveManager::LoadUserType(playerArray[i],type);
            if(type == 0 || type == 2)
            {
                if(rankNum != i)
                {
                    QString tempString = playerArray[i];
                    playerArray[i] = playerArray[rankNum];
                    playerArray[rankNum] = tempString;
                }
                rankNum ++;
            }
        }
        SortPlayerByGrade();
    }
    SetQLabel();
}

void RankWindow::CheckSlotAnswer(bool _flag)
{
    if(_flag != isAnswer)
    {
        isAnswer = _flag;
        UpdateUI();
    }
}

void RankWindow::CheckSlotMaker(bool _flag)
{
    if(_flag == isAnswer)
    {
        isAnswer = !_flag;
        UpdateUI();
    }
}

void RankWindow::SortPlayerByGrade()
{
    if(rankNum == 1)
        return;
    for(int i = 0;i<rankNum;i++)
    {
        for(int j=1;j<rankNum-i;j++)
        {
            int cur,pre;
            if(isAnswer)
                SaveManager::LoadPlayerAnswer(playerArray[j-1],playerData);
            else
                SaveManager::LoadPlayerMaker(playerArray[j-1],playerData);
            pre = playerData.value(SaveManager::GRADE).toInt();
            if(isAnswer)
                SaveManager::LoadPlayerAnswer(playerArray[j],playerData);
            else
                SaveManager::LoadPlayerMaker(playerArray[j],playerData);
            cur = playerData.value(SaveManager::GRADE).toInt();
            if(cur > pre)
            {
                QString tempString = playerArray[j];
                playerArray[j] = playerArray[j-1];
                playerArray[j-1] = tempString;
            }
        }
    }
}

void RankWindow::SetQLabel()
{
    QString tempString;
    for(int i=0;i<rankNum;i++)
    {
        tempString = tempString + "第" + QString::number(i+1) + "名" + "\t\t\t";
        tempString = tempString + "用户名：" + playerArray[i] + '\t';
        if(isAnswer)
            SaveManager::LoadPlayerAnswer(playerArray[i],playerData);
        else
            SaveManager::LoadPlayerMaker(playerArray[i],playerData);
        tempString = tempString + "等级：" + QString::number(playerData.value(SaveManager::GRADE).toInt()) + '\n';
    }
    ui->rank->setText(tempString);
}
