#include <QTime>
#include <QtGui>
#include <QGlobal.h>
#include "zeichenFeld.h"
#include <QObject>
#include <vector>
#include<stdlib.h>//for random
#include <QPoint>

int zeichenFeld::randInt(int low, int high){
    return qrand()%((high+1)-low) + low;
}

zeichenFeld::zeichenFeld(QWidget *parent)
    : QWidget(parent)
{
    setPalette(QPalette(QColor(250, 250, 200)));
    setAutoFillBackground(true);
    setMouseTracking(false);

    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    movetimer=new QTimer(this);
    connect(movetimer, SIGNAL(timeout()), this, SLOT(move()));


}

zeichenFeld::~zeichenFeld()
{
}

void zeichenFeld::paintEvent(QPaintEvent * )
{
    QPainter painter;


    painter.begin( this );

    vector<struct position*>::iterator getx;
    for(getx=falling.begin(); getx!=falling.end();getx++){
        xnew=(*getx)->pos.x();
        ynew=(*getx)->pos.y();
        painter.drawEllipse(xnew,ynew,25,25);

        if(ynew>300){
            //painter.eraseRect(xnew,ynew,25,25); // löscht nur inhalt
            falling.erase(falling.begin());
            update(); // sonst komisches erase
        }
        else{
            ynew+=30;
            (*getx)->pos.setY(ynew);
            //update();
        }
    }

    //vector<struct position> falling;
    //linke obere Ecke: Breite == Hoehe == 50


    painter.end();
}

void zeichenFeld::move()
{
    for(int i=0;i<kreise&&i<=10; i++) // 10mal objektbutton dücken
   {
        int xrand =rand()%500 ; // um an random x zu entstehen
        int yold=10;
        struct position *pos;
        pos=new struct position;
        pos->pos.setX(xrand); // damit ein Kreis nicht jedes Mal ein neues xrand bekommt, sondern seins behält
        pos->pos.setY(yold);
       // QRect bsp= QRect(xrand,30,25,25);
        falling.push_back(pos);
    }

}
