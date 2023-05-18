#ifndef RANKWINDOW_H
#define RANKWINDOW_H

#include <QWidget>
#include <QJsonObject>

namespace Ui {
class RankWindow;
}

class RankWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RankWindow(QWidget *parent = 0);
    ~RankWindow();
    void InitRankWindow(bool);

private:
    Ui::RankWindow *ui;
    bool isAnswer;
    int playerNum;
    int rankNum;
    QString * playerArray;
    QJsonObject playerData;

    void InitConnect();
    void UpdateUI();
    void SortPlayerByGrade();

private slots:
    void ClickBackMenuBtn();
    void CheckSlotAnswer(bool _flag);
    void CheckSlotMaker(bool _flag);

signals:
    void BackToMenu();
};

#endif // RANKWINDOW_H
