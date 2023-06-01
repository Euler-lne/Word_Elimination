#include "multigame.h"
#include "ui_multigame.h"
#include <ctime>
#include <cstdlib>

MultiGame::MultiGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultiGame)
{
    ui->setupUi(this);
    connect(ui->confirmBtn,&QPushButton::clicked,this,&MultiGame::ClickConfirmBtn);
}

MultiGame::~MultiGame()
{
    delete ui;
    if(timerID > 0)
    {
        killTimer(timerID);
        timerID = -1;
    }
}

void MultiGame::UpdatePlayer1(QString _name, int _lastWord)
{
    ui->nameThis->setText(_name);
    ui->lastWordThis->setText(QString::number(_lastWord));
}

void MultiGame::UpdatePlayer2(QString _name, int _lastWord)
{
    ui->nameOther->setText(_name);
    ui->lastWordOther->setText(QString::number(_lastWord));
}

void MultiGame::UpdateWord()
{
    QString _word = words.split(' ')[10-wordNum];
    expectedWord = _word;
    ui->word->setText(_word);
    ui->lineEdit->setEnabled(false);
    ui->lineEdit->setText("");
    ui->confirmBtn->setEnabled(false);
    ui->lastWordThis->setText(QString::number(wordNum));
    int len = _word.length();
    levelTime =  5.5 * ((len / 5.0 + 1)/3); //每一个单词的时间都不一样
    canPressEnter = false;
    startTime = QTime::currentTime();
    timerID = startTimer(100);
}

void MultiGame::timerEvent(QTimerEvent *t)
{
    if(t->timerId() == timerID)
    {
        QTime currentTime = QTime::currentTime();
        int tempInt = 100 - ((startTime.msecsTo(currentTime) / (levelTime * 1000) \
                             + startTime.secsTo(currentTime)/levelTime)*100);
        if(tempInt <= 0)
        {
            tempInt = 0;
            WordTimeOut();
            if(timerID > 0)
            {
                killTimer(timerID);
                timerID = -1;
            }
            canPressEnter = true;
        }
        if(tempInt >= 100)
        {
            tempInt = 100;
        }
        ui->progressBar->setValue(tempInt);
    }
}

void MultiGame::keyPressEvent(QKeyEvent *event)
{
    if((event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) && canPressEnter)
        ClickConfirmBtn();
}

void MultiGame::ClickConfirmBtn()
{
    if(expectedWord == ui->lineEdit->text())
    {
        //正确
        wordNum--;
        emit WordRight(ui->nameOther->text(), wordNum);
        if(wordNum!=0)
        {
            UpdateWord();
        }
        else
        {
            emit EndOfAnswer();
            ui->confirmBtn->setText("等待系统判断");
            ui->confirmBtn->setDisabled(true);
            ui->nameThis->setText(QString::number(wordNum));
        }
    }
    else
    {
        //回答错误
        UpdateWord();
    }
}

void MultiGame::WordTimeOut()
{
    ui->word->setText("");
    ui->lineEdit->setEnabled(true);
    ui->confirmBtn->setEnabled(true);
    ui->lineEdit->setFocus();
}
