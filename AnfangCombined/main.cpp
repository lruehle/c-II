#include "meinwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    meinWidget widget;
    widget.setGeometry(100,100,800,500);
    widget.show();


    return app.exec();
}
