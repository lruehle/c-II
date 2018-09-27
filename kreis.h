#include <QWidget>

class Kreis : public QObject, public QRect{

public:
    Kreis(QObject);
    ~Kreis();
    void move();
private:
    int x,y,lastX, lastY, xrandom;

};
