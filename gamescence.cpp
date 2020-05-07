#include "gamescence.h"

GameScence::GameScence(int level_type)
    : _level_type(level_type){
    setWindowTitle(tr((QString("翻金币:第 ")+QString::number(_level_type)+" 关").toUtf8()));
    setWindowIcon(QIcon(":/res/title_icon.png"));
    setMinimumSize(320,583);
    resize(320,583);
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
    });

    _label_font = new QLabel(this);
    _label_font -> setText(QString("Level:%1").arg(_level_type));
    QFont font;
    font.setFamily("楷体");
    font.setPointSize(20);
    _label_font->setFont(font);

    for(int i=0;i<4;++i){
        for(int j=0;j<4;++j){
            _label_bg[i][j] = new QLabel(this);
            QPixmap pix;
            pix.load(":/res/BoardNode.png");
            _label_bg[i][j]->setGeometry(0,0,pix.width(),pix.height());
            _label_bg[i][j]->setPixmap(pix);
        }
    }
}

void GameScence::paintEvent(QPaintEvent*){
    QPainter *painter = new QPainter(this);
    QPixmap pix;

    //draw background
    pix.load(":/res/PlayLevelSceneBg.png");
    painter->drawPixmap(0,0,this->width(),this->height(),pix);

    //draw main logo
    pix.load(":/res/main_logo.png");
    pix = pix.scaled(pix.width()*.6,pix.height()*.6);
    painter->drawPixmap(width()*0.5-pix.width()*0.5,30,pix);
}
void GameScence::resizeEvent(QResizeEvent*){
    _btn_back->move(this->width()-_btn_back->width(),this->height()-_btn_back->height());
    _label_font->setGeometry(QRect(30,height()-50,120,50));
    for(int i=0;i<4;++i){
        for(int j=0;j<4;++j){
            QPixmap pix;
            pix.load(":/res/BoardNode.png");
            _label_bg[i][j]->move(width()*0.178125+i*pix.width(),height()*0.343053+j*pix.height());
        }
    }
}
GameScence::~GameScence(){
    delete _btn_back;
}
