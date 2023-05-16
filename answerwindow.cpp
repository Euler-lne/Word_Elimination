#include "answerwindow.h"
#include "ui_answerwindow.h"
#include "savemanager.h"


AnswerWindow::AnswerWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnswerWindow)
{
    ui->setupUi(this);
    startGame = new StartGame();//放到InitConnect的前面
    InitConnect();
}

AnswerWindow::~AnswerWindow()
{
    if(startGame != NULL)
        delete startGame;
    startGame = NULL;
    delete ui;
}
void AnswerWindow::InitConnect()
{
    connect(ui->startBtn,&QPushButton::clicked,this,&AnswerWindow::ClickStartBtn);
    connect(ui->rankBtn,&QPushButton::clicked,this,&AnswerWindow::ClickRankBtn);
    connect(ui->accountBtn,&QPushButton::clicked,this,&AnswerWindow::ClickAccountBtn);
    connect(startGame,&StartGame::BackToMenu,this,&AnswerWindow::StartGameToThis);
}
///
/// \brief AnswerWindow::ClickStartBtn
/// 转跳到选择关卡窗口
void AnswerWindow::ClickStartBtn()
{
    this->hide();
    startGame->show();
    startGame->setGeometry(this->geometry());
    startGame->InitStartGame(playerName);
}
void AnswerWindow::ClickRankBtn()
{

}
void AnswerWindow::ClickAccountBtn()
{
    
}


/// 从选择关卡窗口回来
void AnswerWindow::StartGameToThis()
{
    startGame->hide();
    this->show();
    this->setGeometry(startGame->geometry());
}


