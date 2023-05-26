#include "startgame.h"
#include "ui_startgame.h"
#include "savemanager.h"
#include <QDebug>
#include <QMessageBox>
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
    canPressEnter = false;
}

StartGame::~StartGame()
{
    delete ui;
    if(randArray != NULL)
        delete []randArray;
    randArray = NULL;
    if(challengerTimerID > 0)
    {
        killTimer(challengerTimerID);
        challengerTimerID = -1;
    }
    if(timerID > 0)
    {
        killTimer(timerID);
        timerID = -1;
    }
}
void StartGame::InitConnect()
{
    connect(ui->backBtn,&QPushButton::clicked,this,&StartGame::ClickBackMenuBtn);
    connect(ui->confrimBtn,&QPushButton::clicked,this,&StartGame::ClickConfirmBtn);
}

/// 从选择关卡窗口离开，需要保存数据
void StartGame::ClickBackMenuBtn()
{
    if(challengerTimerID > 0)
    {
        killTimer(challengerTimerID);
        challengerTimerID = -1;
    }
    if(timerID > 0)
    {
        killTimer(timerID);
        timerID = -1;
    }
    answer->UpdateData();
    emit BackToMenu();
}

/// 来到此窗口
void StartGame::InitStartGame(my_answer::Answer* _answer)
{
    answer = _answer;
    UpdateUI();
    SelectGameType();
    int key;
    if(gameType == GameType::ENDLESS)
        levelNum = 1;
    else
        levelNum = answer->GetLevelNum();
    key = SetLevel(levelNum);
    if(key == SaveManager::ERROR)
        qDebug() << "错误";
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
    if(key == SaveManager::ERROR)
        return key;
    if(key == SaveManager::NOT_EXIST)
    {
        //关卡还没有出到
        QMessageBox mess(QMessageBox::Question, tr("询问"), "恭喜你已经达到当前的最大关卡数！\n是否要重新开始？");
        QPushButton *button1= (mess.addButton(tr("是"), QMessageBox::AcceptRole));
        QPushButton *button2= (mess.addButton(tr("否"), QMessageBox::YesRole));
        mess.exec();
        if (mess.clickedButton() == button1)
        {
            levelNum = 1;
            return SetLevel(1);
        }
        else if (mess.clickedButton() == button2)
            ClickBackMenuBtn();
        return SaveManager::NOT_EXIST;
    }
    leftWord = levelData.value("num").toInt();
    int totalWord = levelData.value("words").toArray().size();
    if(leftWord > totalWord)
    {
        QMessageBox mess(QMessageBox::Question, tr("询问"), "当前关卡的单词还没有到达最小值。\n是否要重新开始？");
        QPushButton *button1= (mess.addButton(tr("是"), QMessageBox::AcceptRole));
        QPushButton *button2= (mess.addButton(tr("否"), QMessageBox::YesRole));
        mess.exec();
        if (mess.clickedButton() == button1)
        {
            levelNum = 1;
            return SetLevel(1);
        }
        else if (mess.clickedButton() == button2)
            ClickBackMenuBtn();
        return SaveManager::NOT_EXIST;
    }
    levelWords = levelData.value("words").toArray();
    QString tempString = "游戏模式：";
    if(gameType == GameType::CHANLLENGE)
        tempString = tempString + "闯关模式\t";
    else
        tempString = tempString + "无尽模式\t";
    ui->gameType->setText(tempString);
    tempString = "第" + QString::number(_level) + "关";
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
    canPressEnter = false;
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
    if(gameType == GameType::CHANLLENGE)
    {
        startTime = QTime::currentTime();
        challengerTimerID = startTimer(100);
    }
    ui->playInput->setFocus();
}

void StartGame::ClickConfirmBtn()
{
    if(challengerTimerID > 0)
    {
        killTimer(challengerTimerID);
        challengerTimerID = -1;
    }
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
                QString tempString = "恭喜通关";
                ui->playInput->setEnabled(false);
                ui->playInput->setText("");
                ui->leftWord->setText(tempString);
                answer->UpdateEXP(levelNum,-1);
                levelNum ++;
                //玩家相关属性改变，因为当前的关卡数已经增加，所以只有当前关卡数大于玩家自生关数才会增加
                if(levelNum > answer->GetLevelNum() && gameType==GameType::CHANLLENGE)
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
            //回答错误
            if(gameType==GameType::ENDLESS)
                SetWord(randArray[leftWord-1]);
            else
            {
                QMessageBox mess(QMessageBox::Question, tr("询问"), tr("挑战失败\n是否要重新挑战？"));
                QPushButton *button1= (mess.addButton(tr("是"), QMessageBox::AcceptRole));
                QPushButton *button2= (mess.addButton(tr("否"), QMessageBox::YesRole));
                mess.exec();
                if (mess.clickedButton() == button1)
                    SetLevel(levelNum);
                else if (mess.clickedButton() == button2)
                    ClickBackMenuBtn();
            }
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
            if(timerID > 0)
            {
                killTimer(timerID);
                timerID = -1;
            }
            canPressEnter = true;
        }
        if(tempInt >= 100)
        {
            tempInt = 100;
        }
        ui->progressBar->setValue(tempInt);
    }
    else if(t->timerId() == challengerTimerID)
    {
        QTime currentTime = QTime::currentTime();
        int tempInt = 100 - ((startTime.msecsTo(currentTime) / (levelTime * 0.7 * 1000) \
                             + startTime.secsTo(currentTime)/levelTime * 0.7)*100);
        if(tempInt <= 0)
        {
            tempInt = 0;
            ClickConfirmBtn();
        }
        if(tempInt >= 100)
        {
            tempInt = 100;
        }
        ui->progressBar->setValue(tempInt);
    }
}

void StartGame::SelectGameType()
{
    QMessageBox mess(QMessageBox::Information, tr("游戏类型"), tr("请选择游戏类型"));
    QPushButton *button1= (mess.addButton(tr("无尽模式"), QMessageBox::AcceptRole));
    QPushButton *button2= (mess.addButton(tr("闯关模式"), QMessageBox::YesRole));
    mess.exec();

    if (mess.clickedButton() == button1)
        gameType = GameType::ENDLESS;
    else if (mess.clickedButton() == button2)
        gameType = GameType::CHANLLENGE;
    else
        gameType = GameType::ENDLESS;
}

void StartGame::keyPressEvent(QKeyEvent *event)
{
    if((event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) && canPressEnter)
        ClickConfirmBtn();
}
