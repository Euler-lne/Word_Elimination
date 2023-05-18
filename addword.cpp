#include "addword.h"
#include "ui_addword.h"
#include "savemanager.h"
#include <QMessageBox>

AddWord::AddWord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddWord)
{
    ui->setupUi(this);
    InitConnect();
    maker = NULL;
}

AddWord::~AddWord()
{
    delete ui;
}

void AddWord::ClickBackBtn()
{
    maker->UpdateData();
    emit BackToMenu();
}
void AddWord::ClickConfirmBtn()
{
    if(ui->word->text() == "")
    {
        QMessageBox::warning(this,tr("警告"),tr("不能输入空串！\n请重新输入！"));
        return;
    }
    int tempInt = SaveManager::AddWord(ui->word->text());
    if(tempInt == SaveManager::EXIST)
    {
        //提示已经存在了
        QMessageBox::warning(this,tr("警告"),tr("该单词已经在题库中！\n请输入其他单词！"));
    }
    if(tempInt == SaveManager::OK)
    {
        maker->UpdateEXP(ui->word->text().length());
        maker->IncreaseLevelNum();
        maker->UpdateData();
        ui->word->setText("");
        UpdateUI();
    }
}
void AddWord::InitAddWord(my_maker::Maker* _maker)
{
    maker = _maker;
    UpdateUI();
}

void AddWord::InitConnect()
{
    connect(ui->backBtn,&QPushButton::clicked,this,&AddWord::ClickBackBtn);
    connect(ui->confirmBtn,&QPushButton::clicked,this,&AddWord::ClickConfirmBtn);
}
void AddWord::UpdateUI()
{
    QString tempString;
    ui->accountLab->setText(maker->GetName());
    tempString = QString::number(maker->GetLevelNum());
    ui->levelNumLab->setText(tempString);
    tempString = QString::number(maker->GetEXP())+"/"+QString::number(maker->GetMax());
    ui->expLab->setText(tempString);
    tempString = QString::number(maker->GetGrade());
    ui->gradeLab->setText(tempString);
}
