#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QWidget>
#include<QString>
#include<QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString imgPath);

    //X坐标
    int posX;

    //Y坐标
    int posY;

    //正反标志
    bool flag;

    void changeFlag();//执行翻转效果
    QTimer * time1; //正面翻反面定时器
    QTimer * time2; //反面翻正面定时器
    int min = 1;//最小图片
    int max = 8;//最大图片

    bool isAnimation = false; //能否翻转的标志，默认不能翻转，点击时可以

    bool isWin = false; //胜利标志

    //重写按钮的按下事件
    void mousePressEvent(QMouseEvent *e);

signals:

public slots:

};

#endif // MYCOIN_H
