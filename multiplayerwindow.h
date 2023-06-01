#ifndef MULTIPLAYERWINDOW_H
#define MULTIPLAYERWINDOW_H


#include <QWidget>

#include <QTcpSocket>
#include <QHostAddress>
#include <QString>

#include <multigame.h>

#include "answer.h"

namespace Ui {
class MultiplayerWindow;
}

class MultiplayerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MultiplayerWindow(QWidget *parent = 0);
    ~MultiplayerWindow();

    void InitAnswer(my_answer::Answer *_answer);

private:
    Ui::MultiplayerWindow *ui;
    my_answer::Answer *answer;
    QTcpSocket *tcpClient; //定义

    MultiGame *multiGame;

    bool otherEnd;



    const static int FREE;
    const static int GAME;
    const static int CALL;
    const static int CALL_PLAYER;

    void InitConnect();

private slots:
    void ClickBackMenuBtn();
    void ClickConnectBtn();
    void ClickStartBtn();
    void ClickCallGameBtn();
    void ReadData();
    void SendWordNum(QString _name,int _wordNum);
    void EndOfAnswer();

signals:
    void BackToMenu();
};

#endif // MULTIPLAYERWINDOW_H
