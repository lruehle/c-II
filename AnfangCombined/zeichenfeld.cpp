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
    //QPen pen;

    setPalette(QPalette(QColor(210,230,250)));
    setAutoFillBackground(true);
    setMouseTracking(false);
    colorAv=Qt::darkRed;
    color1=Qt::black;
    setFocusPolicy(Qt::StrongFocus);
    xAv = 300;
    yAv = 450;
   // QLabel *lives = new QLabel;
    //lives->setPixmap(".../Images/funnyFischEmpty.jpg");

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
   // QPen pen(Qt::darkRed,10,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);

    QPainter painter;
    //QPen pen;
    //pen.setWidth(10);
    QRectF live1(550.0,15.0,50.0,50.0);//x, y, width, height
    QRectF live2(600.0,15.0,50.0,50.0);
    QRectF live3(650.0,15.0,50.0,50.0);
    int startAngle =40*16;
    int spanAngle= 100*16;
    //painter.setPen(pen); funktioniert nicht...?
    painter.begin (this);
    if(lives==3){ //ShowLives
        painter.setBrush(QBrush(Qt::darkRed,Qt::SolidPattern));
       // painter.setBrush(QBrush(Qt::darkRed,Qt::DiagCrossPattern)); //(now NoBrush!!nowWhite/solidPattern) lives gone-> painted this
        painter.drawPie(live1,startAngle,spanAngle);
        painter.drawPie(live2,startAngle,spanAngle);
        painter.drawPie(live3,startAngle,spanAngle);
    }
    if(lives==2){

        painter.setBrush(QBrush(Qt::white,Qt::SolidPattern)); //lives gone-> painted this
        painter.drawPie(live1,startAngle,spanAngle);
        painter.setBrush(QBrush(Qt::darkRed,Qt::SolidPattern));
        painter.drawPie(live2,startAngle,spanAngle);
        painter.drawPie(live3,startAngle,spanAngle);
    }

    if(lives==1){

        painter.setBrush(QBrush(Qt::white,Qt::SolidPattern)); //lives gone-> painted this
        painter.drawPie(live1,startAngle,spanAngle);
        painter.drawPie(live2,startAngle,spanAngle);
        painter.setBrush(QBrush(Qt::darkRed,Qt::SolidPattern));
        painter.drawPie(live3,startAngle,spanAngle);
    }
    else if(lives==1){

        painter.setBrush(QBrush(Qt::white,Qt::SolidPattern)); //lives gone-> painted this
        painter.drawPie(live1,startAngle,spanAngle);
        painter.drawPie(live2,startAngle,spanAngle);
        painter.drawPie(live3,startAngle,spanAngle);
    }

    /*QPixmap lives(".../Images/funnyFischEmpty.jpg");
    QRectF target(10.0,20.0,80.0,60.0);
    QRectF source(0.0,0.0,70.0,40.0);
    painter.drawPixmap(target, lives, source);*/
    //Avatar:
    QRect rectAv=QRect(xAv, yAv, 40,20);
    painter.fillRect(rectAv, Qt::BrushStyle::SolidPattern);
    painter.fillRect(rectAv, colorAv);
    painter.drawRect(rectAv);

    //Gegner //laufen weiter, weil bei save/load update kommt !fixed
    painter.setBrush(QBrush(Qt::white,Qt::SolidPattern));
    vector<struct position*>::iterator getx;
    for(getx=falling.begin(); getx!=falling.end();getx++){
        xnew=(*getx)->pos.x();
        ynew=(*getx)->pos.y();
        painter.drawEllipse(xnew,ynew,25,25);

        if(ynew>520){
            //painter.eraseRect(xnew,ynew,25,25); // löscht nur inhalt
            //painter.eraseRect(xnew,ynew,25,25);
            falling.erase(falling.begin()); //löscht ersten eintrag im Vektor
            update(); // sonst komisches erase
           // delete *getx;
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
    out<<"l "
      <<lives<<endl;
}

void zeichenFeld::deserialize(QFile &file){
    //vector <struct position *>::iterator posEn;
    struct myPoint *point;
    struct position *pointEn;
    char c;
    for(vector <struct position *>::iterator posEn=falling.begin();posEn!=falling.end();posEn++)
       { delete *posEn;}
         // damit Gegner nicht doppelt gespawnt werden (warum funktionierst du nicht mehr??)
    setUpdatesEnabled(true); //alle enables um weitere updates bei raus und reinklicken ins Widget stoppen
    update();

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
        if(c=='l'){
            in>>lives;

        }

    }
    setUpdatesEnabled(true);
    update();

}
