#ifndef ACCOUNTWINDOW_H
#define ACCOUNTWINDOW_H

#include <QWidget>
#include <QString>
#include "answerwindow.h"
#include "makerwindow.h"
#include "answer.h"
#include "maker.h"

namespace Ui {
class AccountWindow;
}

class AccountWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AccountWindow(QWidget *parent = 0);
    ~AccountWindow();
    void InitAccountWindow(bool _isAnswer, my_answer::Answer* _answer = NULL, my_maker::Maker* _maker = NULL);
    bool GetQuit(){return quit;}

private:
    Ui::AccountWindow *ui;
    my_answer::Answer *answer;
    my_maker::Maker *maker;
    bool isAnswer;
    bool quit;


    void InitConnect();
    void UpdateUI();


private slots:
    void ClickBackMenu();
    void ClickSearchBtn();
    void ClickLogoutBtn();

signals:
    void BackToMenu();
};

#endif // ACCOUNTWINDOW_H
