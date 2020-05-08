#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "mypushbutton.h"
#include "chooselevelsscence.h"
#include <QMainWindow>
#include <QSound>
#include <QPainter>
QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();

    virtual void paintEvent(QPaintEvent*);
    virtual void resizeEvent(QResizeEvent*);
    void dehide();

private:
    Ui::MainScene *ui;

private:
    MyPushButton* _btn_play;
    ChooseLevelsScence * _choLvScence;
};
#endif // MAINSCENE_H
