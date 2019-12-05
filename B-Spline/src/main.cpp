#include "BSpline.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	BSpline w;
	w.show();
	return a.exec();
}
