#ifndef WIDGET_H
#define WIDGET_H

class AnswerWindow;
class MakerWindow;

#include <QWidget>


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
    AnswerWindow *answerWindow;
    MakerWindow *makerWindow;

    void InitConnect();
    void LoginTypeError(int);
    void SwitchWindow(int);
    bool ConfirmPassword();

private slots:
    void ClickLogin();
    void ClickEnroll();
    void MakerToThis();
    void AnswerToThis();
};

#endif // WIDGET_H
