#include "xHKwindow.h"
#include "ui_xHKwindow.h"

xHKWindow::xHKWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::xHKWindow)
{
    ui->setupUi(this);
}

xHKWindow::~xHKWindow()
{
    delete ui;
}
