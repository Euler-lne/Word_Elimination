#include "makerwindow.h"
#include "ui_makerwindow.h"

MakerWindow::MakerWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MakerWindow)
{
    ui->setupUi(this);
    addWord = new AddWord();
    accountWindow = new AccountWindow();
    maker = NULL;
    InitConnect();
}

MakerWindow::~MakerWindow()
{
    delete ui;
    delete addWord;
    delete accountWindow;
    if(maker != NULL)
        delete maker;
    maker = NULL;
}
void MakerWindow::ClickAccountBtn()
{
    this->hide();
    accountWindow->show();
    accountWindow->setGeometry(this->geometry());
    accountWindow->InitAccountWindow(false,NULL,maker);
}
void MakerWindow::ClickAddBtn()
{
    this->hide();
    addWord->show();
    addWord->setGeometry(this->geometry());
    addWord->InitAddWord(maker);
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
    connect(accountWindow,&AccountWindow::BackToMenu,this,&MakerWindow::AccountWindowToThis);
    connect(ui->loginBtn,&QPushButton::clicked,this,&MakerWindow::ClickLogin);
}

void MakerWindow::AddWordToThis()
{
    addWord->hide();
    this->show();
    this->setGeometry(addWord->geometry());
}

void MakerWindow::AccountWindowToThis()
{
    accountWindow->hide();
    this->show();
    this->setGeometry(accountWindow->geometry());
}

void MakerWindow::InitMakerWindow(QString _name)
{
    playerName = _name;
    if(maker == NULL)
        maker = new my_maker::Maker(_name);
}
void MakerWindow::ClickLogin()
{
    maker->UpdateData();
    emit BackToLogin();
}
