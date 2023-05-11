#include "widget.h"
#include "ui_widget.h"
#include "savemanager.h"
#include "game.h"
#include "makerwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QInputDialog>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->noQuestionMaker->setChecked(true); //设置默认选中
    game = new Game();
    makerWindow = new MakerWindow();
    InitConnect();
}

Widget::~Widget()
{
    delete game;
    delete makerWindow;
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
///
/// 出题者0；闯关者1；都是2
void Widget::ClickLogin()
{
    int type;
    if(ui->isQuestionMaker->isChecked())
        type = 0;
    else
        type = 1;
    int key = SaveManager::LoadUser(ui->account->text(),ui->password->text(),type);
    if(key == SaveManager::OK)
    {
        SwitchWindow(type);
    }
    else if(key == SaveManager::TYPE_ERROR)
    {
        //询问是否要将账号升级到其他类型
        LoginTypeError(type);
    }
    else if(key == SaveManager::PASSWORD_ERROR)
    {
        ui->password->setText("");
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
    if(ui->account->text() == "")
    {
        QMessageBox::critical(this, tr("错误"), tr("用户名不可以为空！"));
        return;
    }
    if(ui->password->text() == "")
    {
        QMessageBox::critical(this, tr("错误"), tr("用密码不可以为空！"));
        return;
    }
    int type;
    if(ui->isQuestionMaker->isChecked())
        type = 0;
    else
        type = 1;
    //type是当前选中的是什么，不一定是内存中存储的
    int key = SaveManager::SaveUser(ui->account->text(),ui->password->text(),type);
    if(key == SaveManager::EXIST)
    {
        //账号存在
        ui->password->setText("");
        QMessageBox::warning(this,tr("警告"),tr("账号已经存在！\n请登录！"));
    }
    else if(key == SaveManager::OK || key == SaveManager::CHANGE_TYPE)
    {
        //都正确，或者修改成功
        if(ConfirmPassword())
        {
            ui->password->setText("");
            QMessageBox::information(this,tr("提示"),tr("恭喜您注册成功！\n请登录！"));
        }
        else
        {
            //出现错误，分为两种给情况，密码错误需要删除内存中的账号；改变注册类型则要回到之前的类型
            int temp = type==0 ? 1 : 0;
            //由于类型是可以改变的，所以之前的类型为目前类型的相反类型
            if(key == SaveManager::OK)
                SaveManager::RemoveUser(ui->account->text());
            else
                SaveManager::SaveUser(ui->account->text(),ui->password->text(),temp);
            ui->password->setText("");
            QMessageBox::warning(this,tr("警告"),tr("两次密码不一样！\n请重新输入密码！"));
        }
    }
    else if(key == SaveManager::PASSWORD_ERROR)
    {
        //账号存在密码错误
        ui->password->setText("");
        ui->account->setText("");
        QMessageBox::warning(this,tr("警告"),tr("用户名已经被注册！\n请输入其他用户名！"));
        qDebug() << "账号存在密码错误";
    }
}
void Widget::LoginTypeError(int _type)
{
    QString temp;
    if(_type == 0)
        temp = "您当前的账号为答题者，\n是否要升级为出题者和答题者？";
    else
        temp = "您当前的账号为出题者，\n是否要升级为出题者和答题者？";
    QMessageBox::StandardButton rb1 = QMessageBox::question(this,
                          tr("询问"),
                          temp,
                          QMessageBox::Ok | QMessageBox::Cancel, //OK和Cancel按钮
                          QMessageBox::Ok); //默认
    if(rb1 == QMessageBox::Ok)
    {
        SaveManager::SaveUser(ui->account->text(),ui->password->text(),2);
        QMessageBox::StandardButton rb2 = QMessageBox::question(this,
                              tr("询问"),
                              tr("已经为您升级完成，\n是否要进行登录？"),
                              QMessageBox::Ok | QMessageBox::Cancel, //OK和Cancel按钮
                              QMessageBox::Ok); //默认
        if(rb2 == QMessageBox::Ok)
            SwitchWindow(_type);
    }
    else
        ui->password->setText("");
}
///
/// \brief Widget::SwitchWindow
/// \param _type
/// 没有实现出题者的转跳
///
void Widget::SwitchWindow(int _type)
{
    //闯关者
    if(_type == 1)
    {
        game->SetPlayer(ui->account->text());
        this->hide();
        game->show();
        game->setGeometry(this->geometry());
    }
    else
    {
        this->hide();
        makerWindow->show();
        makerWindow->setGeometry(this->geometry());
    }
}
bool Widget::ConfirmPassword()
{
    bool bOk = false;
    QString sName = QInputDialog::getText(this,
                                          tr("确认密码"),
                                          tr("请再次输入密码"),
                                          QLineEdit::Password,
                                          tr(""),
                                          &bOk);

   if (bOk && sName == ui->password->text())
       return true;
   else
       return false;

}
