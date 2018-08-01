#include "meinwidget.h"
#include "score.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    meinWidget widget;
    widget.setGeometry(100,100,800,500);

    widget.show();

    Score score;
    score.show();



    return app.exec();
}
