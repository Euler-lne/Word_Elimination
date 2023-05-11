#include "game.h"
#include "ui_game.h"
#include "savemanager.h"
#include "answer.h"


Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    InitConnect();
    answer = NULL;
}

Game::~Game()
{
    if(answer != NULL)
        delete answer;
    delete ui;
}
void Game::InitConnect()
{
    connect(ui->startBtn,&QPushButton::clicked,this,&Game::ClickStartBtn);
    connect(ui->rankBtn,&QPushButton::clicked,this,&Game::ClickRankBtn);
    connect(ui->accountBtn,&QPushButton::clicked,this,&Game::ClickAccountBtn);
}
void Game::ClickStartBtn()
{

}
void Game::ClickRankBtn()
{

}
void Game::ClickAccountBtn()
{

}
void Game::SetPlayer(QString _name)
{
    answer = new my_answer::Answer(_name);
    playerName = _name;
    SaveManager::LoadPlayerAnswer(_name, answerData);
    int exp = answerData.value(SaveManager::EXP).toInt();
    int grade = answerData.value(SaveManager::GRADE).toInt();
    int levelNum = answerData.value(SaveManager::LEVEL_NUM).toInt();
    answer->SetExp(exp);
    answer->SetGrade(grade);
    answer->SetLevelNum(levelNum);

}
