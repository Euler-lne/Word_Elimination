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
    connect(ui->listBtn,&QPushButton::clicked,this,&MultiplayerWindow::ClickListBtn);
    connect(tcpClient,&QTcpSocket::readyRead,this,&MultiplayerWindow::ReadData);
    connect(tcpClient,&QTcpSocket::disconnected,this,[=](){
        tcpClient->close();
    });
}

void MultiplayerWindow::ClickBackMenuBtn()
{
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
            tcpClient->write("name " + answer->GetName());
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
        ui->connectBtn->setText("连接服务器");
    }
}
void MultiplayerWindow::ClickCallGameBtn()
{

}
void MultiplayerWindow::ClickListBtn()
{

}
