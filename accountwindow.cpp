#include "accountwindow.h"
#include "ui_accountwindow.h"

AccountWindow::AccountWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountWindow)
{
    ui->setupUi(this);
    answer = NULL;
    maker = NULL;
    InitConnect();
}

AccountWindow::~AccountWindow()
{
    delete ui;
}

void AccountWindow::InitAccountWindow(bool _isAnswer, my_answer::Answer* _answer, my_maker::Maker* _maker)
{
    isAnswer = _isAnswer;
    answer = _answer;
    maker = _maker;
    UpdateUI();
}

void AccountWindow::ClickBackMenu()
{
    emit BackToMenu();
}


void AccountWindow::UpdateUI()
{
    if(isAnswer)
    {
        QString tempString;
        ui->levelNum->setText("闯关数：");
        ui->type->setText("闯关者");
        ui->account->setText(answer->GetName());
        tempString = QString::number(answer->GetEXP());
        ui->exp->setText(tempString);
        tempString = QString::number(answer->GetGrade());
        ui->grade->setText(tempString);
        tempString = QString::number(answer->GetLevelNum());
        ui->levelNum->setText(tempString);
    }
    else
    {
        QString tempString;
        ui->levelNumLab->setText("出题数：");
        ui->type->setText("出题者");
        ui->account->setText(maker->GetName());
        tempString = QString::number(maker->GetEXP());
        ui->exp->setText(tempString);
        tempString = QString::number(maker->GetGrade());
        ui->grade->setText(tempString);
        tempString = QString::number(maker->GetLevelNum());
        ui->levelNum->setText(tempString);
    }
}

void AccountWindow::InitConnect()
{
    connect(ui->backMenuBtn,&QPushButton::clicked,this,&AccountWindow::ClickBackMenu);
}
