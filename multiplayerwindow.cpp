#include "multiplayerwindow.h"
#include "ui_multiplayerwindow.h"
#include <QHostAddress>
#include <QMessageBox>

MultiplayerWindow::MultiplayerWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultiplayerWindow)
{
    ui->setupUi(this);
    tcpClient = new QTcpSocket;
    tcpClient->abort();//取消原有连接
    InitConnect();
}

MultiplayerWindow::~MultiplayerWindow()
{
    delete tcpClient;
    delete ui;
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
}

void MultiplayerWindow::ClickBackMenuBtn()
{
    ui->info->setText("");
    ui->ip->setText("");
    ui->port->setText("");
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
//            tcpClient->write("name " + answer->GetName());
            //初始化网络信息
            ui->connectBtn->setText("断开连接");
        }
        else
        {
            QMessageBox::warning(this,"错误","连接超时，请检查IP地址和端口！");
        }

    }
    else
    {
        tcpClient->close();
        ui->info->setText("");
        ui->connectBtn->setText("连接服务器");
    }
}
void MultiplayerWindow::ClickCallGameBtn()
{

}
void MultiplayerWindow::ClickStartBtn()
{

}
void MultiplayerWindow::ReadData()
{
    QByteArray buffer;
    buffer = tcpClient->readAll();
    if(buffer.split(' ')[0] == "ERROR")
    {
        if(buffer.split(' ')[1]=="1")
        {
            //用户已经被登录
            QMessageBox::warning(this,"警告","用户被登录，如果想继续使用联机功能请退出账号重新登录！");
            ui->info->setText("");
            ui->ip->setText("");
            ui->port->setText("");
            ui->connectBtn->setText("连接服务器");
        }
    }
    else if(buffer.split(' ')[0] == "STATE")
    {
        ui->info->setText(buffer.split(' ')[1]);
    }
}
