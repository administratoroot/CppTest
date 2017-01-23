#include "filternumarrays.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FilterNumArrays w;
    w.show();
    return a.exec();
}
