#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include<QMouseEvent>
#include<QDebug>
#include <QtMultimedia/QSound>
#include <QCursor>
#include <QMouseEvent>
#include "star.h"

namespace Ui {
class game;
}

class game : public QWidget
{
    Q_OBJECT

public:
    explicit game(QWidget *parent = 0);
    ~game();

    void showStar();//开始新一局游戏
    void mousePressEvent(QMouseEvent *e);//处理鼠标点击
    //void mouseMoveEvent(QMouseEvent* event);
    void handleStar(int ,int ,char);//方格的消失
    void shuffleDown();//方格的移动和整理
    void victoryCheck();//游戏结束弹窗处理
    bool isFinish(int,int,char);//判断游戏是否结束

    void deleteStar();//销毁方格
    void refreshScore();//界面分数刷新
    void closeEvent( QCloseEvent * event );//关闭窗口提示
protected:
    int minimumX;//方格区域开始横坐标
    int minimumY;//方格区域开始纵坐标
    int maxRow;//方格行数
    int maxColumn;//方格列数
    int starSize;//方格边长
    star* stars[10][10];//方格内容
    char types[10][10];//方格内容的类型
    int leaveStarNum;//当前未被消除的剩余方格数
    int fillFound;//一次消除中消失的方格数
    int times;//一次游戏中的消除次数
    int score;//分数
    bool used[100];//标记一次消除中已遍历过的方格
    int level;//难度等级
    QString name;//游戏者姓名

    QTimer* pQTimerDoubleClicked; //判断单双击的定时器
    int isDoubleClicked; //区分是单击还是双击

private slots:
    void startgame();//显示本窗口
    void infoRecv(const QString &);//接受数据
    void on_gameBackBtn_clicked();//返回按钮
    void on_newBtn_clicked();//重新开始按钮

    void timerSingleClick(); //定时器事件触发，处理单击任务
    void on_musicPushButton_clicked();//背景音乐播放

private:
    Ui::game *ui;
    QSound *sound;
    QCursor *myCursor;
signals:
    void showmain();//显示游戏开始主界面信号
    void infoSend(int,int);//发送数据信号
};

#endif // GAME_H
