#include "gamescence.h"

GameScence::GameScence(int level_type)
    : _level_type(level_type),_isWin(false){
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
    QSound * back_cou = new QSound(":/res/BackButtonSound.wav",this);
    QSound *win_sou = new QSound(":/res/LevelWinSound.wav",this);
    connect(action_quit,&QAction::triggered,[=](){
        QApplication::quit();
    });

    _btn_back = new MyPushButton(":/res/btn_back.png",":/res/btn_back_select.png",0.3);
    _btn_back->setParent(this);
    connect(_btn_back,&QPushButton::clicked,[=](){
        back_cou->play();
        hide();
        emit hided();
    });

    dataConfig data;
    for(int i=0;i<4;++i){
        for(int j=0;j<4;++j){
            _game_arr[i][j]=data.mData[_level_type][i][j];
        }

    }
    QLabel *winLabel = new QLabel(this);
    QPixmap win_pix;
    win_pix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(QRect(0,0,win_pix.width(),win_pix.height()));
    winLabel->setPixmap(win_pix);

    winLabel->move((width()-win_pix.width())*.5,-win_pix.height());

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


            _coins[i][j] = new MyCoins(_game_arr[i][j]==1?MyCoins::Gold:MyCoins::Silver);
            _coins[i][j]->setParent(this);
            _coins[i][j]->setX(i).setY(j);

            connect(_coins[i][j],&MyCoins::clicked,[=](){
                if(!_isWin){
                    _coins[i][j]->changeStatus();
                    _game_arr[i][j] = !_game_arr[i][j];

                    QTimer::singleShot(300,this,[=](){
                        if(i-1>=0){
                            _coins[i-1][j]->changeStatus();
                            _game_arr[i-1][j] = !_game_arr[i-1][j];
                        }
                        if(i+1<=3){
                            _coins[i+1][j]->changeStatus();
                            _game_arr[i+1][j] = !_game_arr[i+1][j];
                        }
                        if(j-1>=0){
                            _coins[i][j-1]->changeStatus();
                            _game_arr[i][j-1] = !_game_arr[i][j-1];
                        }
                        if(j+1<=3){
                            _coins[i][j+1]->changeStatus();
                            _game_arr[i][j+1] = !_game_arr[i][j+1];
                        }
                        _isWin = true;
                        for(int i=0;i<4;++i){
                            for(int j=0;j<4;++j){
                                if(_coins[i][j]->getStatus()==MyCoins::Silver){
                                    _isWin = false;
                                    break;
                                }
                            }
                        }
                        if(_isWin){
                            qDebug() << "Game WIN!";
                            QPropertyAnimation *animation = new QPropertyAnimation(winLabel,"geometry");
                            animation->setDuration(1000);
                            animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                            animation->setEndValue(QRect(winLabel->x(),winLabel->y()+win_pix.height()*2,winLabel->width(),winLabel->height()));
                            animation->setEasingCurve(QEasingCurve::OutBounce);
                            animation->start();
                            win_sou->play();
                        }
                    });
                }

            });
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
            _coins[i][j]->move(59+i*50,204+j*50);
        }
    }
}
GameScence::~GameScence(){
    delete _btn_back;
}
