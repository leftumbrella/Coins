#ifndef GAMESCENCE_H
#define GAMESCENCE_H

#include "mypushbutton.h"
#include <QMainWindow>
#include <QMenuBar>
#include <QApplication>
#include <QPainter>
#include <QLabel>
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
    QLabel* _label_font;
    MyPushButton * _btn_back;

};

#endif // GAMESCENCE_H
