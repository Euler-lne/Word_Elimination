#include "accountwindow.h"
#include "ui_accountwindow.h"
#include "savemanager.h"
#include <QJsonObject>
#include <QMessageBox>

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
        tempString = QString::number(answer->GetEXP())+"/"+QString::number(answer->GetMax());
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
        tempString = QString::number(maker->GetEXP())+"/"+QString::number(maker->GetMax());
        ui->exp->setText(tempString);
        tempString = QString::number(maker->GetGrade());
        ui->grade->setText(tempString);
        tempString = QString::number(maker->GetLevelNum());
        ui->levelNum->setText(tempString);
    }
    ui->search->setText("");
}

void AccountWindow::InitConnect()
{
    connect(ui->backMenuBtn,&QPushButton::clicked,this,&AccountWindow::ClickBackMenu);
    connect(ui->searchBtn,&QPushButton::clicked,this,&AccountWindow::ClickSearchBtn);
}

void AccountWindow::ClickSearchBtn()
{
    int type;
    int key;
    key = SaveManager::LoadUserType(ui->search->text(),type);
    if(key == SaveManager::NOT_EXIST)
    {
        QMessageBox::warning(this,tr("警告"),tr("该用户不存在！\n请输入其他用户名！"));
        return;
    }
    else if(key == SaveManager::OK)
    {
        QJsonObject answerData;
        QJsonObject makerData;
        QString tempString = "";
        if(type == 1)
        {
            SaveManager::LoadPlayerAnswer(ui->search->text(),answerData);
            tempString = tempString + "用户名：" + ui->search->text() + '\n';
            tempString = tempString + "账号类型：闯关者" + '\n';
            tempString = tempString + "闯关数：" +  QString::number(answerData.value(SaveManager::LEVEL_NUM).toInt()) + '\n';
            tempString = tempString + "等级：" +  QString::number(answerData.value(SaveManager::GRADE).toInt()) + '\n';
            tempString = tempString + "经验:" +  QString::number(answerData.value(SaveManager::EXP).toInt()) + '\n';
        }
        else if(type == 0)
        {
            SaveManager::LoadPlayerAnswer(ui->search->text(),makerData);
            tempString = tempString + "用户名：" + ui->search->text() + '\n';
            tempString = tempString + "账号类型：出题者" + '\n';
            tempString = tempString + "贡献单词数：" +  QString::number(makerData.value(SaveManager::LEVEL_NUM).toInt()) + '\n';
            tempString = tempString + "等级：" +  QString::number(makerData.value(SaveManager::GRADE).toInt()) + '\n';
            tempString = tempString + "经验:" +  QString::number(makerData.value(SaveManager::EXP).toInt()) + '\n';
        }
        else
        {
            SaveManager::LoadPlayerAnswer(ui->search->text(),answerData);
            SaveManager::LoadPlayerMaker(ui->search->text(),makerData);
            tempString = tempString + "用户名：" + ui->search->text() + '\n';
            tempString = tempString + "账号类型：闯关者和出题者" + '\n';
            tempString = tempString + "闯关数：" + QString::number(answerData.value(SaveManager::LEVEL_NUM).toInt()) + '\n';
            tempString = tempString + "闯关等级：" +  QString::number(answerData.value(SaveManager::GRADE).toInt()) + '\n';
            tempString = tempString + "闯关者经验:" +  QString::number(answerData.value(SaveManager::EXP).toInt()) + '\n';
            tempString = tempString + "贡献单词数：" +  QString::number(makerData.value(SaveManager::LEVEL_NUM).toInt()) + '\n';
            tempString = tempString + "出题者等级：" +  QString::number(makerData.value(SaveManager::GRADE).toInt()) + '\n';
            tempString = tempString + "出题者经验:" +  QString::number(makerData.value(SaveManager::EXP).toInt()) + '\n';
        }
        QMessageBox::information(this,tr("消息"),tempString);
    }
}
