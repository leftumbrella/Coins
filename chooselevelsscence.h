#ifndef CHOOSELEVELSSCENCE_H
#define CHOOSELEVELSSCENCE_H

#include "mypushbutton.h"
//#include "mainscene.h"
#include <QMainWindow>
#include <QMenuBar>
#include <QApplication>
#include <QPainter>
class ChooseLevelsScence : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelsScence(QWidget *parent = nullptr);
    ~ChooseLevelsScence();
signals:
    void hided();
private:
    virtual void paintEvent(QPaintEvent*);
    virtual void resizeEvent(QResizeEvent*);
    MyPushButton * _btn_back;
//    MainScene * _mainScene;

};

#endif // CHOOSELEVELSSCENCE_H
