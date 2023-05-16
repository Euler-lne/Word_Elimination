#include "startgame.h"
#include "ui_startgame.h"
#include "savemanager.h"

StartGame::StartGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartGame)
{
    ui->setupUi(this);
    answer = NULL;
    InitConnect();
}

StartGame::~StartGame()
{
    delete ui;
    delete answer;
    answer = NULL;
}
void StartGame::InitConnect()
{
    connect(ui->confirmBtn,&QPushButton::clicked,this,&StartGame::ClickBackMenuBtn);
}

/// 从选择关卡窗口离开
void StartGame::ClickBackMenuBtn()
{
    answer->UpdateData();
    emit BackToMenu();
}

/// 来到此窗口
void StartGame::InitStartGame(QString _name)
{
    playerName = _name;
    if(answer == NULL)
        answer = new my_answer::Answer(_name);
    UpdateUI();
    SaveManager::SaveLevel("happy");
}

void StartGame::UpdateUI()
{
    ui->accountLab->setText(playerName);
    ui->gradeLab->setText(QString::number(answer->GetGrade()));
    ui->expLab->setText(QString::number(answer->GetEXP()));
}

