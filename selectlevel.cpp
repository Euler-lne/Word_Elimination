#include "selectlevel.h"
#include "ui_selectlevel.h"

SelectLevel::SelectLevel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectLevel)
{
    ui->setupUi(this);
    answer = NULL;
    InitConnect();
}

SelectLevel::~SelectLevel()
{
    delete ui;
    delete answer;
    answer = NULL;
}
void SelectLevel::InitConnect()
{
    connect(ui->confirmBtn,&QPushButton::clicked,this,&SelectLevel::ClickBackMenuBtn);
}

/// 从选择关卡窗口离开
void SelectLevel::ClickBackMenuBtn()
{
    answer->UpdateData();
    emit BackToMenu();
}

/// 来到此窗口
void SelectLevel::SetPlayerName(QString _name)
{
    playerName = _name;
    if(answer == NULL)
        answer = new my_answer::Answer(_name);
}

