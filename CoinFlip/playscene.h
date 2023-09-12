#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include"mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = 0);

    PlayScene(int levelIndex);

    //具体选择的关卡号
    int levelIndex;

    //重写绘图事件
    void paintEvent(QPaintEvent *);

    //记录当前关卡的二维数组

    int gameArray[4][4];

    MyCoin * coinBtn[4][4]; //所有的金币按钮

    bool isWin = true; //是否胜利

signals:
    void chooseSceneBack();
public slots:
};

#endif // PLAYSCENE_H
