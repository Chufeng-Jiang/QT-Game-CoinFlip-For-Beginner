#include "mainscene.h"
#include "ui_mainscene.h"
#include <qpainter.h>
#include"mypushbutton.h"
#include<QTimer>
#include<QSound>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
   //主场景的基本配置

    //设置标题
    this->setWindowTitle("Coin Flip Main Scene");

    //设置大小
    this->setFixedSize(320,588);

    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //点击开始中的退出  实现退出游戏
    connect(ui->actionQuit,&QAction::triggered,[=](){
        this->close();
    });

    //开始音效准备
    QSound * startSound = new QSound(":/res/TapButtonSound.wav",this);


    //创建出选择关卡的场景
    chooseScene = new ChooseLevelScene;

    //开始按钮
    MyPushButton * startBtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->move( this->width() *0.5 - startBtn->width() * 0.5, this->height() * 0.7 ); //设置按钮的大小和位置
    startBtn->setParent(this);

    //监听选择关卡场景中的 返回按钮自定义信号
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,[=](){
        chooseScene->hide();
        //设置选中关卡自身的位置，点击返回界面保持原来的位置
        this->setGeometry(chooseScene->geometry());
        this->show();
    });

    //连接信号槽，监听开始按钮点击
    //监听点击事件，执行特效
    connect(startBtn,&MyPushButton::clicked,[=](){
        //qDebug() << "点击了开始按钮";

        //播放音效
        startSound->play();

        startBtn->zoom1();
        startBtn->zoom2();


        QTimer::singleShot(250, this,[=](){
            //延时进入到选择关卡场景
            this->hide(); //自身隐藏

            //设置选中关卡自身的位置
            chooseScene->setGeometry(this->geometry());
            chooseScene->show(); //选择关卡场景显示
        });

    });


}


//利用绘图事件  绘制背景
void MainScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QPixmap pix;

    //加载背景图片
    pix.load(":/res/PlayLevelSceneBg.png");

    painter.drawPixmap(0,0,this->width(),this->height(),pix); //有拉伸的效果


    //加载标题
    pix.load(":/res/Title.png");

    //缩放大小
    pix = pix.scaled(pix.width() * 0.5 , pix.height() * 0.5);

    //10,30是图片放置的开始位置
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);

}



MainScene::~MainScene()
{
    delete ui;
}

