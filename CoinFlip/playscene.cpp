#include"playscene.h"
#include<QDebug>
#include<QMainWindow>
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QLabel>
#include"dataconfig.h"
#include<QPropertyAnimation>
#include<QSound>

PlayScene::PlayScene(int levalIndex)
{

    //记录用户选择的具体关卡号

    this->levelIndex = levalIndex;
    qDebug() << "用户选择的是" << this->levelIndex << "Level";


    //设置窗口固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("Game Play Scene");

    //创建菜单栏
    QMenuBar * bar = this->menuBar();
    this->setMenuBar(bar);
    //创建开始菜单
    QMenu * startMenu = bar->addMenu("Start");
    //创建按钮菜单项
    QAction * quitAction = startMenu->addAction("Quit");
    //点击退出 退出游戏
    connect(quitAction,&QAction::triggered,[=](){this->close();});

    //返回音效
    QSound * backSound = new QSound(":/res/BackButtonSound.wav",this);
    //翻金币音效
    QSound *flipSound = new QSound(":/res/ConFlipSound.wav",this);
    //胜利按钮音效
    QSound *winSound = new QSound(":/res/LevelWinSound.wav",this);


    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");

    backBtn->setParent(this);

    backBtn->move( this->width() - backBtn->width(),  this->height() - backBtn->height());


    connect(backBtn,&MyPushButton::clicked,[=](){
        // qDebug()<<"返回到主场景";

        backSound->play();
        //延时发送返回信号
        QTimer::singleShot(250,this,[=](){
            //this->hide();
            emit this->chooseSceneBack();
        });
    });

    //创建具体用户选择的关卡标签
    QLabel * label = new QLabel;
    label->setParent(this);

    QString str  = QString("Level: %1").arg(this->levelIndex);
    label->setText(str);

    //设置字体和字号
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);

    //设置位置和大小
    label->setGeometry(QRect(30,this->height() - 50, 120,50 ));

    dataConfig config;//第一个对象 获取关卡的数据

    //初始化每个关卡的二维数组
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->gameArray[i][j] = config.mData[this->levelIndex][i][j];
        }
    }

    //提前创建胜利图片，并隐藏在屏幕外部
    QLabel *winlabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winlabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winlabel->setPixmap(tmpPix);
    winlabel->setParent(this);
    winlabel->move((this->width()-tmpPix.width())*0.5, -tmpPix.height());


    //创建金币背景图片
    for(int i = 0 ;i  < 4;i++)
    {
        for(int j = 0 ; j < 4;j ++)
        {
            //QLabel显示图片
            QLabel* label = new QLabel;

            QPixmap pix;
            pix.load(":/res/BoardNode.png");

            label->setGeometry(0,0,pix.width(),pix.height()); //灵活控制小方块的大小
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57 + i*pix.width(),200+j*pix.height());

            QString str;
            if(this->gameArray[i][j] == 1){
                str = ":/res/Coin0001.png";
            }
            else
            {
                  str = ":/res/Coin0008.png";
            }

            //创建金币
            MyCoin * coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(59 + i*pix.width(), 204+j*pix.height());

            //给金币的属性赋值
            coin->posX = i;//x坐标
            coin->posY = j;//y坐标
            coin->flag =gameArray[i][j]; //正反标志

            //将金币放到二维数组中
            coinBtn[i][j]=coin;

            //监听点击按钮 信号
            connect(coin, &MyCoin::clicked,[=](){

                //播放翻金币的音效
                 flipSound->play();

                //将所有的按钮都屏蔽点击
                for(int i=0; i<4; i++)
                {
                    for(int j=0; j<4; j++)
                    {
                        coinBtn[i][j]->isWin = true;
                    }
                }

                coin->changeFlag();

                //同步二维数组，如果以后有保存需求，可以利用数组还愿
                gameArray[i][j] = gameArray[i][j]==0 ? 1:0;


                QTimer::singleShot(300,this,[=](){

                    //翻转周围硬币 检测右侧金币是否可以翻转
                    if(coin->posX+1<=3)
                    {
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        gameArray[coin->posX+1][coin->posY]=
                            gameArray[coin->posX+1][coin->posY] ==0?1:0;
                    }

                    //翻转周围硬币 检测左侧金币是否可以翻转
                    if(coin->posX-1>=0)
                    {
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        gameArray[coin->posX-1][coin->posY]=
                            gameArray[coin->posX-1][coin->posY] ==0?1:0;
                    }

                    //翻转周围硬币 检测下侧金币是否可以翻转
                    if(coin->posY+1<=3)
                    {
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        gameArray[coin->posX][coin->posY+1]=
                            gameArray[coin->posX][coin->posY+1] ==0?1:0;
                    }

                    //翻转周围硬币 检测上侧金币是否可以翻转
                    if(coin->posY-1>=0)
                    {
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        gameArray[coin->posX][coin->posY-1]=
                            gameArray[coin->posX][coin->posY-1] ==0?1:0;
                    }

                    //开启可以让金币点击的状态
                    for(int i=0; i<4; i++)
                    {
                        for(int j=0; j<4; j++)
                        {
                            coinBtn[i][j]->isWin = false;
                        }
                    }

                    //判断是否胜利
                    this->isWin = true;
                    for(int i=0; i<4; i++)
                    {
                        for(int j=0; j<4; j++)
                        {
                            if(coinBtn[i][j]->flag==false) //如果有一个是银币的状态那就是失败
                            {
                                this->isWin = false;
                                break;
                            }
                        }
                    }


                    if(this->isWin)
                    {
                        //胜利音效
                        winSound->play();
                        qDebug()<<"胜利";
                        QPropertyAnimation * animation1
                            = new QPropertyAnimation(winlabel,"geometry");
                        animation1->setDuration(1000);
                        animation1->setStartValue(QRect(winlabel->x(),winlabel->y(),
                                                        winlabel->width(),winlabel->height()));

                        animation1->setEndValue(QRect(winlabel->x(),winlabel->y()+winlabel->height()+this->height()*0.1,
                                                      winlabel->width(),winlabel->height()));

                        animation1->setEasingCurve(QEasingCurve::OutBounce);
                        animation1->start(QAbstractAnimation::DeleteWhenStopped);

                        //禁用所有按钮点击事件
                        for(int i=0; i<4; i++)
                        {
                            for(int j=0; j<4; j++)
                            {
                                coinBtn[i][j]->isWin = true;
                            }
                        }
                       }
                });

            });

         }

    }

}


//重写绘图事件
void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap( 10,30,pix.width(),pix.height(),pix);


}
