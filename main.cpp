#include "widget.h"

#include <QApplication>
//#include<QWheelEvent>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.resize(400, 400);
    w.show();
    return a.exec();
}
