#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QDebug>
#include <QMouseEvent>
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QWidget *parent = nullptr);
    explicit MyPushButton(QString btnPic,QString btnPicSelect = "",double size=0.6);
signals:

private:
    QString _btnPic;
    QString _btnPicSelect;
    virtual void enterEvent(QEvent*);
    virtual void leaveEvent(QEvent*);
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);

    bool setPic(QString pic_path);
    double _size;
};

#endif // MYPUSHBUTTON_H
