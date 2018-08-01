#include <vector>
using namespace std;
#include <QWidget>
#include <QTimer>
#include <QPoint>


struct position
{
    QPoint pos;
};

class zeichenFeld : public QWidget
{
    Q_OBJECT // so i can add slots...
public:
    zeichenFeld(QWidget *parent = 0);
    ~zeichenFeld();

    enum drawType { square, circle };

    void start(void) { timer->start(1000); movetimer->start(2000);kreise=1;/* createtimer->start(1000);*/ increment=1; }
    void stop(void) { timer->stop();movetimer->stop(); /*createtimer->stop();*/ increment=0; }
    void newobjekt(void);
    int randInt(int low, int high);
    int kreise=0;//Anzahl für Kreise, die es gibt
public slots:
    void move();
private:
    QTimer *timer;
    QTimer *movetimer;
    int lastX;
    int lastY;
    int increment;
    int phase;
    int x2,y2,low,high,xnew, ynew;
    vector<struct position*> falling;


protected:
    void paintEvent(QPaintEvent *event);
};

