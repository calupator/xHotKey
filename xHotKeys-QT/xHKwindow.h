#ifndef XHKWINDOW_H
#define XHKWINDOW_H

#include <QMainWindow>

namespace Ui {
class xHKWindow;
}

class xHKWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit xHKWindow(QWidget *parent = 0);
    ~xHKWindow();

private:
    Ui::xHKWindow *ui;
};

#endif // XHKWINDOW_H
