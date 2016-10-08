#ifndef XHKWINDOW_H
#define XHKWINDOW_H

#include <QMainWindow>

#include "..\xHotKeysCore\xHotKeysCore.h"
using namespace xHotKeyCore;

namespace Ui {
class xHKWindow;
}

class xHKWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit xHKWindow(QWidget *parent = 0);
    ~xHKWindow();

    xHotKeys* xHK;
    HWND handle;

protected:
    // Метод для обработки native событий от ОС в Qt
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);

private:
    Ui::xHKWindow *ui;
};

#endif // XHKWINDOW_H
