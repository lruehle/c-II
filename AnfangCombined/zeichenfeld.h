#include<vector>
#include<QWidget>
#include<QBrush>
#include<QTimer>
#include <QFile>
using namespace std;


struct myPoint //pos Avatar
    {
    QPoint point;
   // QColor color;
};

struct position //pos Enemy
{
    QPoint pos;
};


class zeichenFeld : public QWidget
{
    Q_OBJECT
public:
    zeichenFeld(QWidget *parent=0);
    ~zeichenFeld();
    void serialize(QFile &file);
    void deserialize (QFile &file);
    //int randInt(int low, int high); // random spawn between low and high
    void start(){if(lauf==1) {timer->start(500);movetimer->start(1050);setUpdatesEnabled(true);}//{timer->start(10);lauf=1;}
                   if(lauf==2){timer->stop();movetimer->stop();setUpdatesEnabled(false);}}
    int lauf; //sonst kein Zugriff von zeichenfeld
public slots:
    void move();

private:
    //QPixmap *lives;
    //QPen pen;
    QTimer *timer;
    QTimer *movetimer;
    QColor colorAv;
    QColor color1;
    QColor color2;
    QColor color3;
    QColor colorlife;
    int yAv=0, ynew=0;
    int xAv=0, xnew=0;
    int score, low, high;
    int lives=3;
    vector<struct myPoint *> points;
    vector<struct position*> falling;


signals:
    void changed(int score);
protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

};
