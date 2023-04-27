#include "game.h"
#include "ui_game.h"


Game::Game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Game)
{
    ui->setupUi(this);
    InitConnect();
}

Game::~Game()
{
    delete ui;
}
void Game::InitConnect()
{
    connect(ui->startBtn,&QPushButton::clicked,this,&Game::ClickStartBtn);
    connect(ui->rankBtn,&QPushButton::clicked,this,&Game::ClickRankBtn);
    connect(ui->accountBtn,&QPushButton::clicked,this,&Game::ClickAccountBtn);
}
void Game::ClickStartBtn()
{

}
void Game::ClickRankBtn()
{

}
void Game::ClickAccountBtn()
{

}
