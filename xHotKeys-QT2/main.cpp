#include "xHKwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    xHKWindow w;
    w.show();
    w.xHK->Start(w.handle);
    return a.exec();
}
