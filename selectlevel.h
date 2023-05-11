#ifndef SELECTLEVEL_H
#define SELECTLEVEL_H

#include <QWidget>
#include <answer.h>

namespace Ui {
class SelectLevel;
}

class SelectLevel : public QWidget
{
    Q_OBJECT

public:
    explicit SelectLevel(QWidget *parent = 0);  
    ~SelectLevel();
    void SetPlayerName(QString);

public slots:
    void ClickBackMenuBtn();

signals:
    void BackToMenu();

private:
    Ui::SelectLevel *ui;
    void InitConnect();
    QString playerName;
    my_answer::Answer *answer;

};

#endif // SELECTLEVEL_H
