#ifndef GAMESCENCE_H
#define GAMESCENCE_H

#include "mypushbutton.h"
#include "mycoins.h"
#include "dataconfig.h"
#include <QMainWindow>
#include <QMenuBar>
#include <QApplication>
#include <QSound>
#include <QPainter>
#include <QLabel>
#include <QPropertyAnimation>
class GameScence : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameScence(int level_type=1);
    ~GameScence();
signals:
    void hided();
private:
    unsigned int _level_type;
    virtual void paintEvent(QPaintEvent*);
    virtual void resizeEvent(QResizeEvent*);

    QLabel* _label_bg[4][4];
    MyCoins* _coins[4][4];
    QLabel* _label_font;
    MyPushButton * _btn_back;
    int _game_arr[4][4];
    bool _isWin;

};

#endif // GAMESCENCE_H
