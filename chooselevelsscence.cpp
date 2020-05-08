#include "chooselevelsscence.h"
unsigned int ChooseLevelsScence::_levels_num=20;
ChooseLevelsScence::ChooseLevelsScence(QWidget *parent) : QMainWindow(parent){
    setWindowTitle(tr("选择关卡"));
    setWindowIcon(QIcon(":/res/title_icon.png"));
    setMinimumSize(320,583);
    resize(320,583);

    _game_scence = nullptr;
    QMenuBar *bar = new QMenuBar(this);
    setMenuBar(bar);
    QMenu *menu = bar->addMenu(tr("开始"));
    menu->setParent(bar);

    QAction *action_quit = menu->addAction(tr("退出"));
    action_quit->setParent(menu);

    connect(action_quit,&QAction::triggered,[=](){
        QApplication::quit();
    });
    QSound *bacn_sou = new QSound(":/res/BackButtonSound.wav",this);
    QSound *select_sou = new QSound(":/res/TapButtonSound.wav",this);
    _btn_back = new MyPushButton(":/res/btn_back.png",":/res/btn_back_select.png",0.3);
    _btn_back->setParent(this);
    connect(_btn_back,&QPushButton::clicked,[=](){
        bacn_sou->play();
        hide();
        emit hided();
    });

    for(unsigned int i=0;i<_levels_num;++i){
        _levels.push_back(new MyPushButton(":/res/LevelIcon.png",":/res/LevelIcon_select.png",1));
        _labels.push_back(new QLabel(this));

        _levels[i]->setParent(this);
        connect(_levels[i],&MyPushButton::clicked,[=](){
            select_sou->play();
            qDebug() << "You click levels button" << i+1;
            hide();
            if(_game_scence){
                delete _game_scence;
            }
            _game_scence= new GameScence(i+1);
            connect(_game_scence,&GameScence::hided,this,&ChooseLevelsScence::dehide);
            _game_scence->setGeometry(this->geometry());
            _game_scence->show();
        });

        _labels[i]->setText(QString::number(i+1));
        _labels[i]->setFixedSize(_levels[i]->width(),_levels[i]->height());
        _labels[i]->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }



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
    delete _game_scence;
    for(unsigned int i =0;i<_levels_num;++i){
        delete _levels[i];
        delete _labels[i];
    }
}
void ChooseLevelsScence::resizeEvent(QResizeEvent*){
    _btn_back->move(this->width()-_btn_back->width(),this->height()-_btn_back->height());
    for(unsigned int i=0;i<_levels_num;++i){
        _levels[i]->move(width()*0.1+(i%4)*width()*0.2,height()*0.3+(i/4)*height()*0.1);
        _labels[i]->move(width()*0.1+(i%4)*width()*0.2,height()*0.3+(i/4)*height()*0.1);
    }
}
void ChooseLevelsScence::dehide(){
    this->setGeometry(_game_scence->geometry());
    show();
}
