#include <QtGui/QApplication>
#include "confero.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Confero w;
    w.show();
    return a.exec();
}
