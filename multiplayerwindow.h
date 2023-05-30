#ifndef MULTIPLAYERWINDOW_H
#define MULTIPLAYERWINDOW_H


#include <QWidget>

#include <QTcpSocket>
#include <QHostAddress>
#include <QString>

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

    void InitAnswer(my_answer::Answer *_answer){ answer = _answer;}

private:
    Ui::MultiplayerWindow *ui;
    my_answer::Answer *answer;
    QTcpSocket *tcpClient; //定义

    void InitConnect();

private slots:
    void ClickBackMenuBtn();
    void ClickConnectBtn();
    void ClickListBtn();
    void ClickCallGameBtn();
    void ReadData();

signals:
    void BackToMenu();
};

#endif // MULTIPLAYERWINDOW_H
