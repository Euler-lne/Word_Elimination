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
    timer = new QTimer(this);
    InitConnect();
    srand(time(0));
}

StartGame::~StartGame()
{
    delete ui;
    delete timer;
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
    int key;
    key = SetLevel(1);
    if(key == SaveManager::NOT_EXIST)
        qDebug() << "关卡不存在";
}

void StartGame::UpdateUI()
{
    ui->accountLab->setText(playerName);
    ui->gradeLab->setText(QString::number(answer->GetGrade()));
    ui->expLab->setText(QString::number(answer->GetEXP()));
}

int StartGame::SetLevel(int _level)
{
    int key = SaveManager::LoadLevel(_level, levelData);
    levelNum = levelData.value("num").toInt();
    levelTime = levelData.value("time").toDouble();
    levelWords = levelData.value("words").toArray();
    QString tempLevel = "第" + QString::number(_level) + "关";
    ui->levelNum->setText(tempLevel);
    int len = levelWords.size();
    int tempIndex = getRand(0,len-1);
    ui->expected->setText(levelWords.at(tempIndex).toString());
    return key;
}

