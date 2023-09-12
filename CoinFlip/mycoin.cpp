#include "mycoin.h"
#include<QDebug>

MyCoin::MyCoin(QString imgPath)
{
        QPixmap pix;
        bool ret = pix.load(imgPath);
        if(!ret)
        {
            qDebug() << "图片加载失败 %1"<< endl;
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

        //创建两个定时器
        time1 = new QTimer(this);
        time2 = new QTimer(this);

        //监听两个定时器的timeout信号
        connect(time1,&QTimer::timeout,[=](){
            QPixmap pixmap;
            QString str = QString(":/res/Coin000%1.png").arg(this->min++); // 1%占位符
            pixmap.load(str);
            this->setFixedSize(pixmap.width(),pixmap.height());
            this->setStyleSheet("QPushButton{border:0px;}");
            this->setIcon(pixmap);
            this->setIconSize(QSize(pixmap.width(),pixmap.height()));
            if(this->min > this->max){
                this->min = 1; //还原最小值
                //将做动画的标志改为false
                this->isAnimation = false;
                time1->stop();
            }
        });


        connect(time2,&QTimer::timeout,[=](){
            QPixmap pixmap;
            QString str = QString(":/res/Coin000%1.png").arg(this->max--);
            pixmap.load(str);
            this->setFixedSize(pixmap.width(),pixmap.height());
            this->setStyleSheet("QPushButton{border:0px;}");
            this->setIcon(pixmap);
            this->setIconSize(QSize(pixmap.width(),pixmap.height()));
            if(this->max < this->min){
                this->max = 8;
                this->isAnimation = false;
                time2->stop();
            }
        });

}

void MyCoin::changeFlag()
{
        //如果是金币的标志，改为银币
        if(this->flag)//正面
        {
            time1->start(30);
            this->isAnimation = true; //在动画开始时置为true，结束后置为false
            this->flag = false;
        }
        else{ //如果是银币的标志，改为金币
            time2->start(30);
            this->isAnimation = true;
            this->flag = true;
        }
}

// 重写鼠标按下事件
void MyCoin::mousePressEvent(QMouseEvent *e)
{
        if(this->isAnimation || this->isWin) //如果是在动画期间，忽略鼠标的按下事件
        {
            return ;
        }
        else{
            return QPushButton::mousePressEvent(e);
        }
}
