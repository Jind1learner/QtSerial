#include "comtoolwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyComToolWindow w;
    w.show();

    return a.exec();
}
