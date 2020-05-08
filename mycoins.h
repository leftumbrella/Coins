#ifndef MYCOINS_H
#define MYCOINS_H

#include <QPushButton>
#include <QPixmap>
#include <QTimer>
#include <QDebug>
#include <QSound>
class MyCoins : public QPushButton
{
    Q_OBJECT
public:
    enum CoinsType{
        Gold,Silver
    };
    explicit MyCoins(QWidget *parent = nullptr);
    explicit MyCoins(MyCoins::CoinsType = MyCoins::Gold);

    MyCoins& setX(int);
    MyCoins& setY(int);

    void changeStatus();
    inline MyCoins::CoinsType& getStatus(){
        return _type;
    }
signals:
private:
    int _x,_y;
    MyCoins::CoinsType _type;
    QTimer * _tm_G,*_tm_S;
    int _min = 1;
    int _max = 8;
    bool _isDrawing;
    QSound * _tap_sou;

    virtual void mousePressEvent(QMouseEvent*);
};

#endif // MYCOINS_H
