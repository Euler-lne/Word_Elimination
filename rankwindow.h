#ifndef RANKWINDOW_H
#define RANKWINDOW_H

#include <QWidget>

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
    void InitConnect();
    void UpdateUI();

private slots:
    void ClickBackMenuBtn();

signals:
    void BackToMenu();
};

#endif // RANKWINDOW_H
