#include "answerwindow.h"
#include "ui_answerwindow.h"
#include "savemanager.h"


AnswerWindow::AnswerWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnswerWindow)
{
    ui->setupUi(this);
    startGame = new StartGame();//放到InitConnect的前面
    accountWindow = new AccountWindow();
    rankWindow = new RankWindow();
    answer = NULL;
    InitConnect();
}

AnswerWindow::~AnswerWindow()
{
    delete startGame;
    delete accountWindow;
    delete rankWindow;
    if(answer != NULL)
        delete answer;
    answer = NULL;
    delete ui;
}
void AnswerWindow::InitConnect()
{
    connect(ui->startBtn,&QPushButton::clicked,this,&AnswerWindow::ClickStartBtn);
    connect(ui->rankBtn,&QPushButton::clicked,this,&AnswerWindow::ClickRankBtn);
    connect(ui->accountBtn,&QPushButton::clicked,this,&AnswerWindow::ClickAccountBtn);
    connect(startGame,&StartGame::BackToMenu,this,&AnswerWindow::StartGameToThis);
    connect(accountWindow,&AccountWindow::BackToMenu,this,&AnswerWindow::AccountWindowToThis);
    connect(rankWindow,&RankWindow::BackToMenu,this,&AnswerWindow::RankWindowToThis);
    connect(ui->loginBtn,&QPushButton::clicked,this,&AnswerWindow::ClickLogin);
}
///
/// \brief AnswerWindow::ClickStartBtn
/// 转跳到选择关卡窗口
void AnswerWindow::ClickStartBtn()
{
    this->hide();
    startGame->show();
    startGame->setGeometry(this->geometry());
    startGame->InitStartGame(answer);
}
void AnswerWindow::ClickRankBtn()
{
    this->hide();
    rankWindow->show();
    rankWindow->setGeometry(this->geometry());
    rankWindow->InitRankWindow(true);
}
void AnswerWindow::ClickAccountBtn()
{
    this->hide();
    accountWindow->show();
    accountWindow->setGeometry(this->geometry());
    accountWindow->InitAccountWindow(true,answer,NULL);
}


/// 从选择关卡窗口回来
void AnswerWindow::StartGameToThis()
{
    startGame->hide();
    this->show();
    this->setGeometry(startGame->geometry());
}

void AnswerWindow::AccountWindowToThis()
{
    accountWindow->hide();
    this->show();
    this->setGeometry(accountWindow->geometry());
}
void AnswerWindow::InitAnswerWindow(QString _name)
{
    playerName = _name;
    if(answer == NULL)
        answer = new my_answer::Answer(_name);
}
void AnswerWindow::ClickLogin()
{
    answer->UpdateData();
    delete answer;
    answer = NULL;
    emit BackToLogin();
}
void AnswerWindow::RankWindowToThis()
{
    rankWindow->hide();
    this->show();
    this->setGeometry(rankWindow->geometry());
}


