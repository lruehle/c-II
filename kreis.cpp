#include "kreis.h"
#include <QObject>
#include <stdlib.h> // fuer random

/*Kreis::Kreis(QObject):QRect(parent){
    xrandom=rand()%700;
    QRect(xrandom,30,40,40);

}*/

Kreis::Kreis(QObject)
{
    xrandom=rand()%700;
    QRect(xrandom,30,40,40);
}

void Kreis::move(){

    setY(y+10);

}
