#include "tridimApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	tridimApp w;
	w.show();
	return a.exec();
}
