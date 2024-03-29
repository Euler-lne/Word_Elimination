#ifndef MAKERWINDOW_H
#define MAKERWINDOW_H

#include <QWidget>
#include <QString>
#include "maker.h"
#include "addword.h"
#include "accountwindow.h"
#include "rankwindow.h"
class AccountWindow;
class RankWindow;

namespace Ui {
class MakerWindow;
}

class MakerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MakerWindow(QWidget *parent = 0);
    ~MakerWindow();
    void InitMakerWindow(QString _name);

private:
    Ui::MakerWindow *ui;
    QString playerName;
    AddWord *addWord;
    AccountWindow *accountWindow;
    RankWindow *rankWindow;
    my_maker::Maker *maker;

    void InitConnect();


private slots:
    void ClickAddBtn();
    void ClickRankBtn();
    void ClickAccountBtn();
    void ClickLogin();
    void AddWordToThis();
    void RankWindowToThis();
    void AccountWindowToThis();

signals:
    void BackToLogin();
};

#endif // MAKERWINDOW_H
