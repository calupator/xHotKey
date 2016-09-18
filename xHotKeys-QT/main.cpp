#include "xHKwindow.h"
#include <QApplication>

#include "..\xHotKeysCore\Beholder.h"
using namespace xHotKeyCore;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    xHKWindow w;
    w.show();

    Beholder* bh = new Beholder();
    QString name = QString::fromWCharArray(bh->GetName(0));
    delete bh;

    return a.exec();
}
