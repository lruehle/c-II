#include <QWidget>
#include <QLCDNumber>
#include <QTimer>


class Score:public QLCDNumber {
Q_OBJECT
public:
    Score(Score::QWidget *parent=0);
    ~Score();
private slots:
    void showScore();
private:
    int score;
};
