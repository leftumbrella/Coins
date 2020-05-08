#include "mycoins.h"

MyCoins::MyCoins(QWidget *parent) : QPushButton(parent){

}
MyCoins::MyCoins(MyCoins::CoinsType type)
    :_type(type),_isDrawing(false){
    _tap_sou = new QSound(":/res/ConFlipSound.wav",this);
    QPixmap pix;
    switch (_type) {
        case MyCoins::Gold:
        pix.load(":/res/Coin0001.png");
        break;
    case MyCoins::Silver:
        pix.load(":/res/Coin0008.png");
        break;
    }
    setFixedSize(pix.width(),pix.height());
    setStyleSheet("QPushButton{border:0px;}");
    setIcon(pix);
    setIconSize(QSize(pix.width(),pix.height()));
    _tm_G = new QTimer(this);
    _tm_S = new QTimer(this);

    connect(_tm_G,&QTimer::timeout,[=](){
        QPixmap pix;
        QString pic_path = QString(":/res/Coin000%1.png").arg(_min++);
        pix.load(pic_path);
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(_min > _max){
            _min = 1;
            _isDrawing=false;
            _tm_G->stop();
        }
    });
    connect(_tm_S,&QTimer::timeout,[=](){
        QPixmap pix;
        QString pic_path = QString(":/res/Coin000%1.png").arg(_max--);
        pix.load(pic_path);
        qDebug() << "At timer in pic_path:"<<pic_path;
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(_min > _max){
            _max = 8;
            _isDrawing=false;
            _tm_S->stop();
        }
    });
}
MyCoins& MyCoins::setX(int x){
    _x=x;
    return *this;
}

MyCoins& MyCoins::setY(int y){
    _y=y;
    return *this;
}
void MyCoins::changeStatus(){
     _tap_sou->play();
    switch (_type) {
        case MyCoins::Gold:
            qDebug() << "At Coins change";
            _isDrawing=true;
            _tm_G->start(30);
            _type = MyCoins::Silver;
            break;
        case MyCoins::Silver:
            _isDrawing=true;
            _tm_S->start(30);
            _type = MyCoins::Gold;
            break;
    }
}
void MyCoins::mousePressEvent(QMouseEvent* e){
    if(_isDrawing){
        return;
    }else {
        QPushButton::mousePressEvent(e);
    }
}
