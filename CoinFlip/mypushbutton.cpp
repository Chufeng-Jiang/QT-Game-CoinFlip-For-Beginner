#include "mypushbutton.h"
#include<QDebug>
#include<QPropertyAnimation>

MyPushButton::MyPushButton(QString normalImg, QString pressImg)
{
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;

    //QPixmap加载图标
    QPixmap pix;

    bool ret = pix.load(normalImgPath);
    if(!ret)
    {
        // %1是占位，参数为后面的.arg(normalImg)中的normalImg
        QString srt = QString( "图片加载失败 %1").arg(normalImg);
        qDebug() << srt;
        return;
    }


    //设置图片大小
    this->setFixedSize( pix.width(),pix.height());

    //设置不规则图片样式，border:0px表示不要边框
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(pix);

    //设置图标大小
    this->setIconSize(QSize( pix.width(),pix.height()));
}

void MyPushButton::zoom1()
{

    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");

    //设置动画时间间隔
    animation->setDuration(200);

    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置弹起效果, QEasingCurve::OutBounce 为弹跳效果
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //让动画执行
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}


void MyPushButton::zoom2()
{

    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");

    //设置动画时间间隔
    animation->setDuration(200);

    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));


    //设置弹起效果
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //让动画执行
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}


//重写鼠标按下
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    //如果按下图片的路径不为空，代表需要切换图片
    if(this->pressImgPath != "")
    {
        QPixmap pix;
        bool ret = pix.load(pressImgPath);
        if(!ret)
        {
            QString srt = QString( "图片加载失败 %1").arg(pressImgPath);
            qDebug() << srt;
            return;
        }


        //设置图片大小
        this->setFixedSize( pix.width(),pix.height());

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize( pix.width(),pix.height()));

    }

    //点击的响应事件抛给父类
    QPushButton::mousePressEvent(e);

}
//重写鼠标释放
void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressImgPath != "")
    {
        QPixmap pix;
        bool ret = pix.load(this->normalImgPath);
        if(!ret)
        {
            QString srt = QString( "图片加载失败 %1").arg(normalImgPath);
            qDebug() << srt;
            return;
        }


        //设置图片大小
        this->setFixedSize( pix.width(),pix.height());

        //设置不规则图片样式
        this->setStyleSheet("QPushButton{border:0px;}");

        //设置图标
        this->setIcon(pix);

        //设置图标大小
        this->setIconSize(QSize( pix.width(),pix.height()));

    }


    //点击的响应事件抛给父类
    QPushButton::mouseReleaseEvent(e);

}
