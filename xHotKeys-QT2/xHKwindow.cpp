#include "xHKwindow.h"
#include "ui_xHKwindow.h"

xHKWindow::xHKWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::xHKWindow)
{
    ui->setupUi(this);

    handle = NULL;
    xHK = new xHotKeys();

    xHK->Init();
}

xHKWindow::~xHKWindow()
{
    delete xHK;
    delete ui;
}

bool xHKWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)
    Q_UNUSED(result)
    // Преобразуем указатель message в MSG WinAPI
    MSG* msg = reinterpret_cast<MSG*>(message);

    if(!handle)
        handle = msg->hwnd;
    	
	if (xHK->HotKeys(msg))
		return true;
    return false;
}
