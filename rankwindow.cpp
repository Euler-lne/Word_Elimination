#include "rankwindow.h"
#include "ui_rankwindow.h"

RankWindow::RankWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RankWindow)
{
    ui->setupUi(this);
    InitConnect();
}

RankWindow::~RankWindow()
{
    delete ui;
}

void RankWindow::InitConnect()
{
    connect(ui->backMenuBtn,&QPushButton::clicked,this,&RankWindow::ClickBackMenuBtn);
}

void RankWindow::ClickBackMenuBtn()
{
    emit BackToMenu();
}
void RankWindow::InitRankWindow(bool _isAnswer)
{
    isAnswer = _isAnswer;
    ui->answerRadio->setChecked(isAnswer);
    ui->makerRadio->setChecked(!isAnswer);
    UpdateUI();
}

void RankWindow::UpdateUI()
{
    if(isAnswer)
    {
        ui->rankLab->setText("答题者排名");
    }
    else
    {
        ui->rankLab->setText("出题者排名");
    }
}
