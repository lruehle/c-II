#include <QtGui>
#include <QBrush>
#include <QKeyEvent>
//#include<QGraphicsRectItem>
#include "zeichenfeld.h"
#include <QMessageBox>
#include<QPen>
#include <QPoint>
#include <vector>
#include<stdlib.h>//for random
#include <QGlobal.h>
#include <QTime>


/*int zeichenFeld::randInt(int low, int high){
    return qrand()%((high+1)-low) + low; //Source!!
}*/

zeichenFeld::zeichenFeld(QWidget *parent):QWidget(parent)
{
    setFixedSize(700,500);
    QPen pen;
    pen.setWidth(3);
    setPalette(QPalette(QColor(0,51,25)));
    setAutoFillBackground(true);
    setMouseTracking(false);
    colorAv=Qt::darkRed;
    color1=Qt::black;
    setFocusPolicy(Qt::StrongFocus);
    xAv = 300;
    yAv = 450;
    timer=new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    movetimer=new QTimer(this);
    connect(movetimer, SIGNAL(timeout()), this, SLOT(move()));
}

zeichenFeld::~zeichenFeld()
{
    for(vector <struct myPoint *>::iterator pos=points.begin();pos!=points.end();pos++)
        delete *pos; // der itterator geht durch alle Felder des Vektors, gelöscht wird worauf er zeigt
}

void zeichenFeld::paintEvent(QPaintEvent *event)
{
  // if(lauf==1){
    QPainter painter;
    painter.begin (this);

    //Avatar:
    QRect rectAv=QRect(xAv, yAv, 40,20);
    painter.fillRect(rectAv, Qt::BrushStyle::SolidPattern);
    painter.fillRect(rectAv, colorAv);
    painter.drawRect(rectAv);

    //Gegner //laufen weiter, weil bei save/load update kommt
    vector<struct position*>::iterator getx;
    for(getx=falling.begin(); getx!=falling.end();getx++){
        xnew=(*getx)->pos.x();
        ynew=(*getx)->pos.y();
        painter.drawEllipse(xnew,ynew,25,25);

        if(ynew>520){
            //painter.eraseRect(xnew,ynew,25,25); // löscht nur inhalt
            falling.erase(falling.begin()); //löscht ersten eintrag im Vektor
            update(); // sonst komisches erase
        }
        else{
            ynew+=20; // schnelles Fallen bei update liegt hieran...
            (*getx)->pos.setY(ynew);
            //update();
        }
    }

    painter.end();
   //}

}


void zeichenFeld::keyPressEvent(QKeyEvent *event)
{

    if(event->key()==Qt::Key_A){
            //enums?
        if(xAv>0){
            xAv-=40; // bewegt wird jeweils die Hälfte der x-Länge/yHöhe mit einem klick
            }
     }
    if(event->key()==Qt::Key_D){
            //enums?
        if(xAv<650)
            xAv+=40;
    }

    if(event->key()==Qt::Key_W){
        if(yAv>300){
            yAv-=15;
        }
    }
    if(event->key()==Qt::Key_S){
        if(yAv<470){
            yAv+=15;
        }
    }

    struct myPoint *point;
    point=new struct myPoint; // speichert x Koordinate
    point->point.setX(xAv);
    point->point.setY(yAv);
    points.push_back((point));
   // update(); bei jedem update, fliegen die enemies schneller
}

void zeichenFeld::move()
{
   // for(int i=0;i<lauf&&i<=10; i++) // 10mal objektbutton dücken-> alt!
   //{
        int xrand =rand()%500 ; // um an random x zu entstehen
        int yold=10;
        struct position *pos;
        pos=new struct position;
        pos->pos.setX(xrand); // damit ein Kreis nicht jedes Mal ein neues xrand bekommt, sondern seins behält
        pos->pos.setY(yold);
       // QRect bsp= QRect(xrand,30,25,25);
        falling.push_back(pos);
        score+=50;
        emit changed(score);
   // }

}

void zeichenFeld::serialize(QFile &file)//Bsp 3
{

    vector<struct myPoint *>::iterator pos;
    vector <struct position *>::iterator posEn;
    QTextStream out(&file);
    for (pos=points.begin();pos!=points.end(); pos++)
    {
        out<< "p "
           <<(*pos)->point.x()<<" "<<(*pos)->point.y()<<endl; //struct mypoint
    }
    for (posEn=falling.begin();posEn!=falling.end();posEn++)
    {
        out<<"e "
          <<(*posEn)->pos.x()<<" "<<(*posEn)->pos.y()<<endl; //Punkt aus struct position
    }
    out<<"s "
      <<score<<endl;
}

void zeichenFeld::deserialize(QFile &file){
    vector <struct position *>::iterator posEn;
    struct myPoint *point;
    struct position *pointEn;
    char c;
    for(vector <struct position *>::iterator posEn=falling.begin();posEn!=falling.end();posEn++)
        delete *posEn; // damit Gegner nicht doppelt gespawnt
    setUpdatesEnabled(true); //alle enables um weitere updates bei raus und reinklicken ins Widget stoppen
    update();
    //int x;
    setUpdatesEnabled(false);
    QTextStream in(&file);
    while (in.status()==QTextStream::Ok)
    {
        in>>c;
        if(in.status()==QTextStream::ReadPastEnd)break;

       /* if(c!='p')
        {
            QMessageBox::warning(this,tr("Objektfehler"),
                                 tr("Dieser Objekttyp nicht bekannt: ")+ c, QMessageBox::Ok);
            return;
        }*/
        if (c=='p'){
          point=new struct myPoint;

            in>>xAv>>yAv;
            point->point.setX(xAv);
            point-> point.setY(yAv);
            in>>c;
       /* QMessageBox::warning(this,tr("Test"),
                             tr("x war ")+ x, QMessageBox::Ok);*/
            points.push_back(point);



        }
        if (c=='e'){
          pointEn=new struct position;

            in>>xnew>>ynew;
            pointEn->pos.setX(xnew);
            pointEn->pos.setY(ynew);
            in>>c;
       /* QMessageBox::warning(this,tr("Test"),
                             tr("x war ")+ x, QMessageBox::Ok);*/
            falling.push_back(pointEn);
        }
        if(c=='s'){
            in>>score;
            emit changed(score);
        }

    }
    setUpdatesEnabled(true);
    update();
}
