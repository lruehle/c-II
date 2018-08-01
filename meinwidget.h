#include<QWidget>
#include "zeichenfeld.h"
#include<QLCDNumber>
//#include <QLabel>

class meinWidget:public QWidget
{
    Q_OBJECT // macro für QT Bibs

public:
    meinWidget(QWidget *parent=0);
private:
    zeichenFeld *meinZeichenFeld;


private slots:

   void start(void);
   void saver(void);
   void loader(void);

};
