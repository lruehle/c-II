#include "meinwidget.h"
// Qt5 add:
#include <QApplication>
#include <QTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    meinWidget w;
    QTime time = QTime::currentTime();
    w.setGeometry(100, 100, 500, 355);
    w.show();

    return a.exec();
}
