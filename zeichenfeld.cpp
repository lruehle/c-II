#include <QtGui>
#include <QBrush>
#include <QKeyEvent>
#include<QGraphicsRectItem>
#include "zeichenfeld.h"
#include "score.h"
#include <QMessageBox>
#include<QPen>



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



}

zeichenFeld::~zeichenFeld()
{
    for(vector <struct myPoint *>::iterator pos=points.begin();pos!=points.end();pos++)
        delete *pos; // der itterator geht durch alle Felder des Vektors, gelöscht wird worauf er zeigt
}

void zeichenFeld::paintEvent(QPaintEvent *event)
{

    QPainter painter;
    painter.begin (this);

    //Avatar:

    QRect rectAv=QRect(xAv, yAv, 40,20);
    painter.fillRect(rectAv, Qt::BrushStyle::SolidPattern);
    painter.fillRect(rectAv, colorAv);
    painter.drawRect(rectAv);
    painter.end();

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
        if(xAv<650){
            xAv+=40;
        }
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
    update();
}


/*void zeichenFeld::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton)
    {
        xAv-=35;
    }
    if(event->button()==Qt::RightButton)
    {
        xAv+=35;
    }
    struct myPoint *point;

    point=new struct myPoint;
    point->point.setX(xAv);
    points.push_back((point));
    update();
}*/


void zeichenFeld::serialize(QFile &file)//Bsp 3
{

    vector<struct myPoint *>::iterator pos;
    QTextStream out(&file);
    for (pos=points.begin();pos!=points.end(); pos++)
    {
        out<< "p "
           <<(*pos)->point.x()<<" "<<(*pos)->point.y()<<endl;
    }
}

void zeichenFeld::deserialize(QFile &file){
    struct myPoint *point;
    char c;
    //int x;

    QTextStream in(&file);
    while (in.status()==QTextStream::Ok)
    {
        in>>c;
        if(in.status()==QTextStream::ReadPastEnd)break;

        if(c!='p')
        {
            QMessageBox::warning(this,tr("Objektfehler"),
                                 tr("Dieser Objekttyp nicht bekannt: ")+ c, QMessageBox::Ok);
            return;
        }
        point=new struct myPoint;

        in>>xAv>>yAv;
        point ->point.setX(xAv);
        point->point.setY(yAv);
        in>>c; // Leerstellen werden vom '>>' Operator 'konmsumiert';
        // Zeilenenden nicht.
       /* QMessageBox::warning(this,tr("Test"),
                             tr("x war ")+ x, QMessageBox::Ok);*/
        points.push_back(point);


    }
    update();
}
