#include "na_qt_test2.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	NA_Qt_test2 w;
	w.show();
	return a.exec();
}
