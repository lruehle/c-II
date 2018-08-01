#include<vector>
#include<QWidget>
#include<QBrush>
#include<QTimer>
#include <QFile>
using namespace std;


struct myPoint
    {
    QPoint point;
    QColor color;
};

class zeichenFeld : public QWidget
{
public:
    zeichenFeld(QWidget *parent=0);
    ~zeichenFeld();
    void serialize(QFile &file);
    void deserialize (QFile &file);
    void start(void){timer->start(10);}//{timer->start(10);lauf=1;}

    //void punktestand();

//signals:
  //  void scoreChanged(int Punkte);
private:
    QTimer *timer;
    QColor colorAv;
    QColor color1;
    QColor color2;
    QColor color3;
    QColor colorlife;
    vector<struct myPoint *> points;
    //int lauf;
    int yAv=0;
    int xAv=0;
    //int Punkte=0;


protected:
    void paintEvent(QPaintEvent *event);
   // void keyReleaseEvent(QKeyEvent *event);
    void keyPressEvent(QKeyEvent *event);//override?
    //void mousePressEvent(QMouseEvent *event);

};
