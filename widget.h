#ifndef WIDGET_H
#define WIDGET_H

class Game;

#include <QWidget>
#include "game.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    void InitConnect();
    Game *game;
public slots:
    void ClickLogin();
    void ClickEnroll();
};

#endif // WIDGET_H
