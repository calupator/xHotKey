#ifndef XHKWINDOW_H
#define XHKWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_xHKWindow.h"

class xHKWindow : public QMainWindow
{
	Q_OBJECT

public:
	xHKWindow(QWidget *parent = 0);
	~xHKWindow();

private:
	Ui::xHKWindowClass ui;
};

#endif // XHKWINDOW_H
