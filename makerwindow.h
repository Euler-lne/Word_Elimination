#ifndef MAKERWINDOW_H
#define MAKERWINDOW_H

#include <QWidget>
#include <QString>
#include "addword.h"

namespace Ui {
class MakerWindow;
}

class MakerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MakerWindow(QWidget *parent = 0);
    ~MakerWindow();
    void SetPlayerName(QString _name){playerName = _name;}

private:
    Ui::MakerWindow *ui;
    QString playerName;
    AddWord *addWord;

    void InitConnect();


private slots:
    void ClickAddBtn();
    void ClickRankBtn();
    void ClickAccountBtn();
    void AddWordToThis();
};

#endif // MAKERWINDOW_H
