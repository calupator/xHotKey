#include "xHKWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	xHKWindow w;
	w.show();
	return a.exec();
}
