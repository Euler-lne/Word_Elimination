#include "makerwindow.h"
#include "ui_makerwindow.h"

MakerWindow::MakerWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MakerWindow)
{
    ui->setupUi(this);
}

MakerWindow::~MakerWindow()
{
    delete ui;
}
