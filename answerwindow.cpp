#include "answerwindow.h"
#include "ui_answerwindow.h"
#include "savemanager.h"
#include "answer.h"


AnswerWindow::AnswerWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnswerWindow)
{
    ui->setupUi(this);
    //防止用到空指针，把初始化变量放在前面
    answer = NULL;
    selectLevel = new SelectLevel();//放到InitConnect的前面
    InitConnect();
}

AnswerWindow::~AnswerWindow()
{
    if(answer != NULL)
        delete answer;
    if(selectLevel != NULL)
        delete selectLevel;
    answer = NULL;
    selectLevel = NULL;
    delete ui;
}
void AnswerWindow::InitConnect()
{
    connect(ui->startBtn,&QPushButton::clicked,this,&AnswerWindow::ClickStartBtn);
    connect(ui->rankBtn,&QPushButton::clicked,this,&AnswerWindow::ClickRankBtn);
    connect(ui->accountBtn,&QPushButton::clicked,this,&AnswerWindow::ClickAccountBtn);
    connect(selectLevel,&SelectLevel::BackToMenu,this,&AnswerWindow::SeletLevelToThis);
}
///
/// \brief AnswerWindow::ClickStartBtn
/// 转跳到选择关卡窗口
void AnswerWindow::ClickStartBtn()
{
    this->hide();
    selectLevel->show();
    selectLevel->setGeometry(this->geometry());
    answer->UpdateData();
    selectLevel->SetPlayerName(playerName);
}
void AnswerWindow::ClickRankBtn()
{

}
void AnswerWindow::ClickAccountBtn()
{
    
}

/// 来到此窗口
void AnswerWindow::SetPlayerName(QString _name)
{
    playerName = _name;
    if(answer == NULL)
        answer = new my_answer::Answer(_name);
}

/// 从选择关卡窗口回来
void AnswerWindow::SeletLevelToThis()
{
    answer->LoadData();
    selectLevel->hide();
    this->show();
    this->setGeometry(selectLevel->geometry());
}


