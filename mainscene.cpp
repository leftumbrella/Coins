#include "mainscene.h"
#include "ui_mainscene.h"

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene){
    ui->setupUi(this);
    QSound *start_sou = new QSound(":/res/TapButtonSound.wav",this);
    _choLvScence = new ChooseLevelsScence();
    setWindowTitle(tr("翻金币"));
    setWindowIcon(QIcon(":/res/title_icon.png"));
    resize(320,583);
    connect(ui->action_quit,&QAction::triggered,[=](){
        this->close();
    });

    //btn_start create
    _btn_play = new MyPushButton(":/res/btn_play.png",":/res/btn_play_select.png");
    _btn_play->setParent(this);
    connect(_btn_play,&QPushButton::clicked,[=](){
        start_sou->play();
        hide();
        _choLvScence->setGeometry(this->geometry());
        _choLvScence->show();
    });

    connect(_choLvScence,&ChooseLevelsScence::hided,this,&MainScene::dehide);
}

void MainScene::paintEvent(QPaintEvent*){


    QPainter *painter = new QPainter(this);
    QPixmap pix;

    //draw background
    pix.load(":/res/PlayLevelSceneBg.png");
    painter->drawPixmap(0,0,this->width(),this->height(),pix);

    //draw main logo
    pix.load(":/res/main_logo.png");
    pix = pix.scaled(pix.width()*.3,pix.height()*.3);
    painter->drawPixmap(10,30,pix);

}

void MainScene::resizeEvent(QResizeEvent*){
    _btn_play->move(this->width()*.5-_btn_play->width()*.5,this->height()*.7);
}
void MainScene::dehide(){
    setGeometry(_choLvScence->geometry());
    show();
}

MainScene::~MainScene(){
    delete ui;
    delete _btn_play;
    delete _choLvScence;
}

