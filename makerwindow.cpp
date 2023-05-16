#include "makerwindow.h"
#include "ui_makerwindow.h"

MakerWindow::MakerWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MakerWindow)
{
    ui->setupUi(this);
    addWord = new AddWord();
    InitConnect();
}

MakerWindow::~MakerWindow()
{
    delete ui;
    delete addWord;
}
void MakerWindow::ClickAccountBtn()
{

}
void MakerWindow::ClickAddBtn()
{
    this->hide();
    addWord->show();
    addWord->setGeometry(this->geometry());
    addWord->InitAddWord(playerName);
}
void MakerWindow::ClickRankBtn()
{

}

void MakerWindow::InitConnect()
{
    connect(ui->accountBtn,&QPushButton::clicked,this,&MakerWindow::ClickAccountBtn);
    connect(ui->addBtn,&QPushButton::clicked,this,&MakerWindow::ClickAddBtn);
    connect(ui->rankBtn,&QPushButton::clicked,this,&MakerWindow::ClickRankBtn);
    connect(addWord,&AddWord::BackToMenu,this,&MakerWindow::AddWordToThis);
}

void MakerWindow::AddWordToThis()
{
    addWord->hide();
    this->show();
    this->setGeometry(addWord->geometry());
}
