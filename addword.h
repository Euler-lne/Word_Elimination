#ifndef ADDWORD_H
#define ADDWORD_H

#include <QWidget>
#include <QString>
#include "maker.h"

namespace Ui {
class AddWord;
}

class AddWord : public QWidget
{
    Q_OBJECT

public:
    explicit AddWord(QWidget *parent = 0);
    ~AddWord();
    void InitAddWord(my_maker::Maker*);

private:
    Ui::AddWord *ui;
    my_maker::Maker *maker;

    void ClickConfirmBtn();
    void ClickBackBtn();
    void InitConnect();
    void UpdateUI();

signals:
    void BackToMenu();
};

#endif // ADDWORD_H
