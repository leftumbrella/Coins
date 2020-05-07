#include "chooselevelsscence.h"

ChooseLevelsScence::ChooseLevelsScence(QWidget *parent) : QMainWindow(parent){
    setWindowTitle(tr("选择关卡"));
    setWindowIcon(QIcon(":/res/title_icon.png"));
    setMinimumSize(320,583);
    resize(320,583);

//    _mainScene = new MainScene();
    QMenuBar *bar = new QMenuBar(this);
    setMenuBar(bar);
    QMenu *menu = bar->addMenu(tr("开始"));
    menu->setParent(bar);

    QAction *action_quit = menu->addAction(tr("退出"));
    action_quit->setParent(menu);

    connect(action_quit,&QAction::triggered,[=](){
        QApplication::quit();
    });

    _btn_back = new MyPushButton(":/res/btn_back.png",":/res/btn_back_select.png",0.3);
    _btn_back->setParent(this);
    connect(_btn_back,&QPushButton::clicked,[=](){
        hide();
        emit hided();
//        _mainScene->show();
    });
}


void ChooseLevelsScence::paintEvent(QPaintEvent*){
    QPainter *painter = new QPainter(this);
    QPixmap pix;

    //draw background
    pix.load(":/res/OtherSceneBg.png");
    painter->drawPixmap(0,0,this->width(),this->height(),pix);

    //draw main logo
    pix.load(":/res/main_logo.png");
    pix = pix.scaled(pix.width()*.6,pix.height()*.6);
    painter->drawPixmap(width()*0.5-pix.width()*0.5,30,pix);
}
ChooseLevelsScence::~ChooseLevelsScence(){
    delete _btn_back;
}
void ChooseLevelsScence::resizeEvent(QResizeEvent*){
    _btn_back->move(this->width()-_btn_back->width(),this->height()-_btn_back->height());
}
