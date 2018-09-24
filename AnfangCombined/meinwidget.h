#include<QWidget>
#include<QPushButton>
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
    QLCDNumber *score;
    QAbstractButton *start;

private slots:

   void starter(void);
   void saver(void);
   void loader(void);
   //void stop(void);

};
