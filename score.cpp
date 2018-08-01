#include "score.h"
#include"meinwidget.h"
#include <QTimer>

Score::Score(QWidget *parent):QLCDNumber(parent){
    setSegmentStyle(Filled);
    QTimer *scoretimer = new QTimer(this);
    connect(scoretimer, SIGNAL(timeout()), this, SLOT(showScore()));
    scoretimer->start(1000);
    score=50;
    showScore();//so no 1s delay when first called

    setWindowTitle(tr("Score"));
}

Score::~Score(){
    score=0;
}

void Score::showScore(){
    score+=50;
    display(score);
}
