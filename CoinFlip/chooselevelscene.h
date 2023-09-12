#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    //Overwrite the event
    void paintEvent(QPaintEvent *);

    PlayScene * playScene;

signals:
    //Click the Back Button and produce the signals
    void chooseSceneBack();
};

#endif // CHOOSELEVELSCENE_H
