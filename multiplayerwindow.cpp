#include "multiplayerwindow.h"
#include "ui_multiplayerwindow.h"
#include "savemanager.h"
#include <QHostAddress>
#include <QMessageBox>
#include <QInputDialog>
#include <QMessageBox>
const int MultiplayerWindow::FREE = 0;
const int MultiplayerWindow::GAME = 1;
const int MultiplayerWindow::CALL = 2;
const int MultiplayerWindow::CALL_PLAYER = 3;
MultiplayerWindow::MultiplayerWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultiplayerWindow)
{
    ui->setupUi(this);
    tcpClient = new QTcpSocket;
    multiGame = new MultiGame;
    tcpClient->abort();//取消原有连接
    InitConnect();
    ui->callGameBtn->setDisabled(true);
    ui->startBtn->setDisabled(true);
    otherEnd = false;
}

MultiplayerWindow::~MultiplayerWindow()
{
    delete tcpClient;
    delete multiGame;
    delete ui;
    answer->UpdateData();
}

void MultiplayerWindow::InitConnect()
{
    connect(ui->backMenuBtn,&QPushButton::clicked,this,&MultiplayerWindow::ClickBackMenuBtn);
    connect(ui->connectBtn,&QPushButton::clicked,this, &MultiplayerWindow::ClickConnectBtn);
    connect(ui->callGameBtn,&QPushButton::clicked,this,&MultiplayerWindow::ClickCallGameBtn);
    connect(ui->startBtn,&QPushButton::clicked,this,&MultiplayerWindow::ClickStartBtn);
    connect(tcpClient,&QTcpSocket::readyRead,this,&MultiplayerWindow::ReadData);
    connect(tcpClient,&QTcpSocket::disconnected,this,[=](){
        tcpClient->close();
    });
    connect(multiGame,&MultiGame::WordRight,this,&MultiplayerWindow::SendWordNum);
    connect(multiGame,&MultiGame::EndOfAnswer,this,&MultiplayerWindow::EndOfAnswer);
}

void MultiplayerWindow::InitAnswer(my_answer::Answer *_answer)
{
    ui->callGameBtn->setDisabled(true);
    ui->startBtn->setDisabled(true);
    answer = _answer;
    ui->accountLab->setText("用户名：" + answer->GetName());
}

void MultiplayerWindow::ClickBackMenuBtn()
{
    ui->info->setText("");
    ui->ip->setText("");
    ui->port->setText("");
    if((ui->connectBtn->text() =="断开连接"))
    {
            ui->connectBtn->setText("连接服务器");
            tcpClient->close();
    }
    answer->UpdateData();
    emit BackToMenu();
}

void MultiplayerWindow::ClickConnectBtn()
{
    if(ui->connectBtn->text() == "连接服务器")
    {
        unsigned short port = ui->port->text().toUShort();
        QString ip = ui->ip->text();
        tcpClient->connectToHost(QHostAddress(ip),port);
        if(tcpClient->waitForConnected(5000))
        {
            //把用户信息传输给客户端
            QString tempString = "NAME " + answer->GetName() + ";";
            tcpClient->write(tempString.toUtf8());
            tempString = "WORD " + SaveManager::GetWord() + ";";
            tcpClient->write(tempString.toUtf8());
            //初始化网络信息
            ui->connectBtn->setText("断开连接");

            ui->callGameBtn->setDisabled(false);
            ui->startBtn->setDisabled(false);
        }
        else
        {
            QMessageBox::warning(this,"错误","连接超时，请检查IP地址和端口！");
            ui->callGameBtn->setDisabled(true);
            ui->startBtn->setDisabled(true);
        }

    }
    else if(ui->connectBtn->text() == "断开连接")
    {
        tcpClient->close();
        ui->info->setText("");
        ui->connectBtn->setText("连接服务器");
        ui->callGameBtn->setDisabled(true);
        ui->startBtn->setDisabled(true);
    }
}
void MultiplayerWindow::ClickCallGameBtn()
{
    //发起挑战
    //玩家还是处于空闲状态
    bool bOk = false;
    QString sName = QInputDialog::getText(this,
                                         "QInputdialog_Name",
                                         "请输入当前空闲的玩家",
                                         QLineEdit::Normal,
                                         "",
                                         &bOk
                                         );

    if (bOk && !sName.isEmpty()) {
        QString tempString = "STATE " +QString::number(CALL_PLAYER) + ' ' + sName +  ";";
        tcpClient->write(tempString.toUtf8());
    }
}
void MultiplayerWindow::ClickStartBtn()
{
    if(ui->startBtn->text()=="开始匹配")
    {
        //开始匹配
        QString tempString = "STATE " + QString::number(CALL) + ";";
        tcpClient->write(tempString.toUtf8());
        ui->connectBtn->setDisabled(true);
        ui->callGameBtn->setDisabled(true);
        ui->backMenuBtn->setDisabled(true);
        ui->startBtn->setText("取消匹配");
    }
    else if(ui->startBtn->text() == "取消匹配")
    {
        ui->connectBtn->setDisabled(false);
        ui->callGameBtn->setDisabled(false);
        ui->backMenuBtn->setDisabled(false);
        ui->startBtn->setText("开始匹配");
        tcpClient->write("STATE FREE;");
    }

    //转跳
}
void MultiplayerWindow::ReadData()
{
    QByteArray inBuffer;
    inBuffer = tcpClient->readAll();
    for(int j=0;j<inBuffer.split(';').size();j++)
    {
        QByteArray buffer = inBuffer.split(';')[j];
        if(buffer.split(' ')[0] == "ERROR")
        {
            if(buffer.split(' ')[1]=="1")
            {
                //用户已经被登录
                QMessageBox::warning(this,"警告","用户被登录，如果想继续使用联机功能请退出账号重新登录！");
                ui->info->setText("");
                ui->ip->setText("");
                ui->port->setText("");
                ClickConnectBtn();
                break;
            }
            else if(buffer.split(' ')[1]=="2")
            {
                //用户已经被登录
                QMessageBox::warning(this,"警告","当前词库较少，请添加词库后再进行登录！");
                ui->info->setText("");
                ui->ip->setText("");
                ui->port->setText("");
                ClickConnectBtn();
                break;
            }
        }
        else if(buffer.split(' ')[0] == "STATE_INFO")
        {
            ui->info->setText(buffer.split(' ')[1]);
        }
        else if(buffer.split(' ')[0]=="WORD")
        {
            for(int i=1;i<buffer.split(' ').size();i++)
                SaveManager::AddWord(buffer.split(' ')[i]);
        }
        else if(buffer.split(' ')[0]=="ASK_GAME")//接受挑战者
        {
            QString name = buffer.split(' ')[1];
            int rect = QMessageBox::information(this,
                                                "接收到挑战",
                                                "玩家:"+name+"向您发起挑战是否接收？",
                                                QMessageBox::Ok|QMessageBox::Cancel,
                                                QMessageBox::Ok);
            if(rect == QMessageBox::Ok)
            {
                //接受挑战
                //发起挑战者为name
                QString tempString = "STATE " +QString::number(GAME) + ' ' + "ASK_GAME_TRUE " + name +  ";";
                tcpClient->write(tempString.toUtf8());

                //设置界面初始信息
                multiGame->UpdatePlayer1(answer->GetName(),10);
                multiGame->UpdatePlayer2(name,10);
            }
            else
            {
                //放弃挑战
                QString tempString = "STATE " +QString::number(GAME) + ' ' + "ASK_GAME_FALSE " + name +  ";";
                tcpClient->write(tempString.toUtf8());
            }
        }
        else if(buffer.split(' ')[0]=="ASK_GAME_FALSE")
        {
            int state = buffer.split(' ')[1].toInt();
            switch (state) {
            case 1:
                QMessageBox::warning(this,"发起挑战失败","玩家离线或者玩家已经开始游戏！\n");
                break;
            case 2:
                QString name = buffer.split(' ')[2];
                QMessageBox::warning(this,"拒绝","玩家："+ name +"拒绝接受挑战\n");
                break;
            }
        }
        else if(buffer.split(' ')[0]=="ASK_GAME_TRUE") //发起挑战者接受到的
        {
            QString name = buffer.split(' ')[1]; //对手的名字

            //设置界面初始信息
            multiGame->UpdatePlayer1(answer->GetName(),10);
            multiGame->UpdatePlayer2(name,10);
        }
        else if(buffer.split(' ')[0]=="MATCH")
        {
            QString name = buffer.split(' ')[1]; //对手名字

            //设置界面初始信息
            multiGame->UpdatePlayer1(answer->GetName(),10);
            multiGame->UpdatePlayer2(name,10);
        }
        else if(buffer.split(' ')[0]=="GAME_DATA")
        {
            QString words = "";
            for(int i=1;i<=10;i++)
            {
                words += buffer.split(' ')[i] + ' ';
            }
            words.trimmed();
            this->hide();
            multiGame->show();
            multiGame->setGeometry(this->geometry());
            multiGame->SetWords(words);
        }
        else if(buffer.split(' ')[0]=="GAME_WORD_NUM")
        {
            QString name = buffer.split(' ')[1];
            int wordNum = buffer.split(' ')[2].toInt();
            multiGame->UpdatePlayer2(name, wordNum);
            if(wordNum == 0)
            {
                otherEnd = true;
            }
        }
    }
}

void MultiplayerWindow::SendWordNum(QString _name,int _wordNum)
{
    //如果另一个玩家已经结束就不会向另一个玩家发送当前的关卡信息
    if(otherEnd)
        return;
    QString tempString = "GAME_WORD_NUM " + _name + ' ' + QString::number(_wordNum) +  ";";
    tcpClient->write(tempString.toUtf8());
}

void MultiplayerWindow::EndOfAnswer()
{
    QString tempString;
    multiGame->hide();
    this->show();
    this->setGeometry(multiGame->geometry());
    if(otherEnd)
    {
        //挑战失败
        tempString = "挑战失败，扣除100点经验值！";
        answer->UptateEXP(-100);
        if(answer->GetGrade() < 3)
        {
            QMessageBox::information(this,"等级不足","当前等级为"+QString::number(answer->GetGrade())+'\n'+"等级不足3级，不能进行多人游戏！\n请自行退出！");
            ui->callGameBtn->setDisabled(true);
            ui->startBtn->setDisabled(true);
            ui->connectBtn->setText("等级不足");
            tcpClient->close();
        }
    }
    else
    {
        //挑战成功
        tempString = "挑战成功，获得300点经验值！";
        answer->UptateEXP(300);
    }
    QMessageBox::information(this,"挑战信息",tempString);
    ui->connectBtn->setDisabled(false);
    ui->callGameBtn->setDisabled(false);
    ui->backMenuBtn->setDisabled(false);
    ui->startBtn->setText("开始匹配");
    tcpClient->write("STATE FREE;");
}
