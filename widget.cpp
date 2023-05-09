#include "widget.h"
#include "ui_widget.h"
#include "savemanager.h"
#include <QMessageBox>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->isQuestionMaker->setChecked(true); //设置默认选中
    game = new Game();
    InitConnect();
}

Widget::~Widget()
{
    delete game;
    delete ui;
}
void Widget::InitConnect()
{
    connect(ui->login,&QPushButton::clicked,this,&Widget::ClickLogin);
    connect(ui->enroll,&QPushButton::clicked,this,&Widget::ClickEnroll);
}
///
/// \brief Widget::ClickLogin
/// 按下注册键需要执行的操作
/// 1.需要判断用户是否存在，密码是否正确
/// 2.如果密码正确且类型选择正确转跳到game窗口
/// 3.如果密码正确且类型选择错误转提示是否在参加相应的角色
/// 4.如果密码不正确弹出提示
void Widget::ClickLogin()
{
    int type;
    if(ui->isQuestionMaker->isChecked())
        type = 0;
    else
        type = 1;
    int key = SaveManager::LoadUser(ui->account->text(),ui->password->text(),type);
    if(key == SaveManager::RIGHT)
    {
        this->hide();
        game->show();
        game->setGeometry(this->geometry());
    }
    else if(key == SaveManager::TYPE_ERROR)
    {
        QMessageBox::critical(this, tr("错误"), tr("类型错误！"));
    }
    else if(key == SaveManager::PASSWORD_ERROR)
    {
        QMessageBox::critical(this, tr("错误"), tr("密码错误！"));
    }
}
///
/// \brief Widget::ClickEnroll
/// 1.判断用户是否存在且密码是否正确
/// 2.如果用户存在且密码不正确或者，那么弹出提示说明用户已经存在，提醒用户重登录
/// 3.如果用户不存在要求用户再次确认密码
/// 4.如果确认成功弹出注册成功的信息，用户可以选择登录。
/// 5.如果密码不一样则重新输入密码。
void Widget::ClickEnroll()
{
    int type;
    if(ui->isQuestionMaker->isChecked())
        type = 0;
    else
        type = 1;
    int key = SaveManager::SetUser(ui->account->text(),ui->password->text(),type);
    if(key == SaveManager::EXIST)
    {
        //账号存在
        qDebug() << "账号存在";
    }
    else if(key == SaveManager::RIGHT)
    {
        //都正确，或者修改成功
        qDebug() << "都正确，或者修改成功" ;
    }
    else if(key == SaveManager::PASSWORD_ERROR)
    {
        //账号存在密码错误
        qDebug() << "账号存在密码错误";
    }
}
