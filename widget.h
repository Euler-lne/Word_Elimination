#ifndef WIDGET_H
#define WIDGET_H

class Game;
class MakerWindow;

#include <QWidget>
#include "game.h"
#include "makerwindow.h"

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
    void LoginTypeError(int);
    void SwitchWindow(int);
    bool ConfirmPassword();
    Game *game;
    MakerWindow *makerWindow;

public slots:
    void ClickLogin();
    void ClickEnroll();
};

#endif // WIDGET_H
