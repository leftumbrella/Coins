#ifndef CHOOSELEVELSSCENCE_H
#define CHOOSELEVELSSCENCE_H

#include "mypushbutton.h"
#include "gamescence.h"
#include <QMainWindow>
#include <QMenuBar>
#include <QApplication>
#include <QPainter>
#include <QVector>
#include <QLabel>
#include <QSound>
class ChooseLevelsScence : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelsScence(QWidget *parent = nullptr);
    ~ChooseLevelsScence();
    void dehide();
signals:
    void hided();
private:

    static unsigned int _levels_num;

    virtual void paintEvent(QPaintEvent*);
    virtual void resizeEvent(QResizeEvent*);
    MyPushButton * _btn_back;

    GameScence* _game_scence;
    QVector<MyPushButton*> _levels;
    QVector<QLabel*> _labels;


};

#endif // CHOOSELEVELSSCENCE_H
