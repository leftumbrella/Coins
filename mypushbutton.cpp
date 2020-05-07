#include "mypushbutton.h"

MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent){

}
MyPushButton::MyPushButton(QString btnPic,QString btnPicSelect,double size)
    :_btnPic(btnPic),_btnPicSelect(btnPicSelect),_size(size){

    setPic(_btnPic);


}

void MyPushButton::enterEvent(QEvent*){
    if(_btnPicSelect.isEmpty()){
        return;
    }
    setPic(_btnPicSelect);
}
void MyPushButton::leaveEvent(QEvent*){
    if(_btnPic.isEmpty()){
        return;
    }
    setPic(_btnPic);
}
bool MyPushButton::setPic(QString pic_path){
    QPixmap pix;
    if(!pix.load(pic_path)){
        qDebug() << "The btnPicSelect path failed!::" << _btnPicSelect;
        return false;
    }
    pix = pix.scaled(pix.width()*_size,pix.height()*_size);
    setFixedSize(pix.width(),pix.height());//set btn size
    setStyleSheet("QPushButton{border:0px;}");//set btn style used css
    setIcon(pix);//set picture
    setIconSize(QSize(pix.width(),pix.height()));//set picture size
    return true;
}
