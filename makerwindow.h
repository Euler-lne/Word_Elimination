#ifndef MAKERWINDOW_H
#define MAKERWINDOW_H

#include <QWidget>

namespace Ui {
class MakerWindow;
}

class MakerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MakerWindow(QWidget *parent = 0);
    ~MakerWindow();

private:
    Ui::MakerWindow *ui;
};

#endif // MAKERWINDOW_H
