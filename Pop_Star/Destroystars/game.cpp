#include "game.h"
#include "ui_game.h"
#include "recorddialog.h"
#include "enddialog.h"

#include<QMessageBox>
#include<QDateTime>
#include<QSqlQuery>
#include <QTimer>
#include <QMovie>
#include <QCursor>
#include <QMouseEvent>
#include <QEvent>
#include <QDir>
game::game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::game)
{
    ui->setupUi(this);
    setFixedSize(580,640);
    minimumX = 40;
    minimumY = 110;
    maxRow = 10;
    maxColumn = 10;
    starSize = 50;

    //处理背景音乐相关
    sound=new QSound("F:/zhouhan/Destroystars/pray-Zhangyixing.wav",this);
    isDoubleClicked = 0; //初始化不点击
    pQTimerDoubleClicked = new QTimer(this); //新建定时器
    connect(pQTimerDoubleClicked,SIGNAL(timeout()),this,SLOT(timerSingleClick())); //关联定时器和槽函数

    //初始化stars数组，使方格未生成时，数组里的值不为任意值
    for(int i=0;i<maxRow;i++)
        memset(stars[i],0,sizeof(stars[i]));
    this->setMouseTracking(true);

    myCursor=new QCursor(QPixmap(":/star/images/shubiao.png"),0,0);    //-1,-1表示热点位于图片长宽的2^-1处,0、0可使热点位于左上角
    this->setCursor(*myCursor);

}

game::~game()
{
    delete ui;
}

void game::showStar()
{
    leaveStarNum = maxRow*maxColumn;
    fillFound = 0;
    score = 0;
    times = 0;

    refreshScore();//刷新分数

    int x,y,colorNum;
    //计算颜色种类数
    if(level == 1)colorNum = 4;
    if(level == 2)colorNum = 5;
    if(level == 3)colorNum = 6;

    //消除屏幕上仍剩下的方格,使所有指针值为NULL
    deleteStar();

    //生成方格
    srand(QDateTime::currentDateTime().toTime_t());
    for(int row=0; row<maxRow; row++)
    {
        for(int col=0; col<maxColumn; col++)
        {
            //stars[row][col] = NULL;
            types[row][col] = rand()%colorNum;
            stars[row][col] = new star(this,types[row][col]);
            //计算每个格子的起始坐标
            x = minimumX + col*starSize;
            y = minimumY + row*starSize;
            stars[row][col]->setGeometry(x,y,x+starSize,y+starSize);
            stars[row][col]->show();
        }
    }
}

void game::mousePressEvent(QMouseEvent *e)
{
    //获取鼠标坐标
    int x = e->x();
    int y = e->y();

    //点击在非方格区域
    if(x<minimumX || x>minimumX+maxColumn*starSize ||
            y<minimumY || y>minimumY+maxRow*starSize)
        return;

    //计算鼠标位置对应的方格行列坐标
    int row = (y-minimumY)/starSize;
    int col = (x-minimumX)/starSize;

    //点击在方格已被消除区域
    if(stars[row][col]==NULL)return;

    handleStar(row,col,-1);//消除方格

    //此次点击并未消除方格时
    if(fillFound <= 0)return;
    else times++;


    leaveStarNum -= fillFound;
    score += fillFound*fillFound*5;
    refreshScore();

    shuffleDown();//调整方格位置
    victoryCheck();//检测该局游戏是否结束
}

void game::handleStar(int row,int col,char type)
{
    bool first = false;//标志是否为鼠标按下的方格（第一个处理的方格）

    if(type == -1){//当是鼠标按下的方格时
        first = true;
        type = types[row][col];
        fillFound = 0;
        for(int i=0; i<maxRow*maxColumn; i++)
            used[i] = false;
    }

    if(stars[row][col] == NULL)
        return;//遍历到已消除的方格，返回上层递归
    if(col<0 || col>=maxColumn || row<0 || row>=maxRow)
        return;//遍历出方格区域，返回上层递归
    if(used[row*maxColumn+col])
        return;//遍历到此次递归已处理过的方格，返回上层递归
    if(type != types[row][col])
        return;//该方格与上一层递归中的方格颜色不同，返回上层递归

    used[row*maxColumn+col] = true;//标记已走过当前方格

    //按顺时针方向
    handleStar(row-1,col,type);
    handleStar(row,col+1,type);
    handleStar(row+1,col,type);
    handleStar(row,col-1,type);

    if(first && fillFound == 0)return;//鼠标点击的方格周围无同颜色方格时

    delete stars[row][col];//消除一块方格
    stars[row][col] = NULL;
    fillFound += 1;
}

//处理缩进
void game::shuffleDown()
{
    int topx,topy;//星星的x、y坐标
    int block;//空星星数
    int col,row;

    for(col = 0;col<maxColumn;col++)//本循环处理向下缩进，按列自下而上扫描
    {
        block = 0;
        for(row = maxRow-1;row >=0;row--)
        {
            if(stars[row][col] == NULL){//如果扫描到空白
                block++;//可供向下缩进的空白数+1
            }
            else
            {
                if(block >0)//如果该列存在空白，则需要向下缩进
                {
                    //计算方格新坐标
                    topx = minimumX+col*starSize;
                    topy = minimumY+(row+block)*starSize;

                    //重新设置方块位置
                    stars[row][col]->setGeometry(topx,topy,topx+starSize,topy+starSize);

                    //与对应空白方格交换内容
                    star *swap;
                    swap = stars[row+block][col];
                    stars[row+block][col] = stars[row][col];
                    stars[row][col] = swap;
                    char temp;
                    temp = types[row+block][col];
                    types[row+block][col] = types[row][col];
                    types[row][col] = temp;

                }
            }
        }

    }

    block = 0;
    for(col=0;col<maxColumn;col++ )//本循环处理向左缩进,只有一列全为空白，星星才能向左缩进
    {
        if(stars[maxRow-1][col] == NULL)//如果该列最底层星星为空白，则该列全部空白
        {
            block++;//可供向左缩进的空白数+1
        }
        else
        {
            if(block>0)
            {
                for(row=maxRow-1;row>-1;row--)
                {
                    //不对该列上部的空白块做处理
                    if(stars[row][col] == NULL)	//continue;
                        break;

                    topx = minimumX+(col-block)*starSize;
                    topy = minimumY+row*starSize;

                    //重新设置方块位置
                    stars[row][col]->setGeometry(topx,topy,topx+starSize,topy+starSize);

                    //通过交换将空白块移至该行最右端
                    star *swap;
                    swap = stars[row][col-block];
                    stars[row][col-block] = stars[row][col];
                    stars[row][col] = swap;
                    char temp;
                    temp = types[row][col-block];
                    types[row][col-block] = types[row][col];
                    types[row][col] = temp;

                }
            }
        }
    }
}

//判断游戏是否可结束（剩余方块是否可继续消除）
bool game::isFinish(int row,int col,char type)
{
    if(row<0 || row>maxRow-1 || col>maxRow-1 ||col<0)//如果递归超出方块组范围
    {
        return false;//可结束
    }

    if(stars[row][col] == NULL)//如果递归到空方块
    {
        return false;//可结束
    }

    if(type == types[row][col])//如果颜色相同
    {
        return true;//可继续
    }

    //向上向右遍历，所有遍历结果都可结束才结束游戏，有一种情况可继续都继续游戏
    return isFinish(row-1,col,types[row][col])||isFinish(row,col+1,types[row][col]);

}

void game::victoryCheck()
{
    if(!isFinish(maxRow-1,0,-1))//从左下角开始判断方格是否还可消除
    {
        int s;
        //计算剩余方格的加减分
        if(leaveStarNum>=10){
            s = (leaveStarNum-10)*20;
            score -= s;
            if(score<=0)score = 0;
            QMessageBox box(QMessageBox::Warning,"加减分",
                            QString(tr("剩余%1个方格，减去%2分")).arg(leaveStarNum).arg(s));
            box.exec();
        }else if(leaveStarNum<10){
            s = (10-leaveStarNum)*20;
            score += s;
            QMessageBox box(QMessageBox::Warning,"加减分",
                            QString(tr("剩余%1个方格，加上%2分")).arg(leaveStarNum).arg(s));
            box.exec();
        }
        //刷新分数
        refreshScore();

        //从数据库中读出最高纪录
        QSqlQuery query;
        if(level == 1){
            query.exec("select scores from stars where type = 'easy'");
        }else if(level == 2){
            query.exec("select scores from stars where type = 'middle'");
        }else if(level == 3){
            query.exec("select scores from stars where type = 'sophisticated'");
        }
        query.next();
        //判断是否创造纪录
        if(score>query.value(0).toInt()){//未创造
            recordDialog n;
            connect(this,SIGNAL(infoSend(int,int)),&n,SLOT(infoRecv(int,int)));
            emit infoSend(level,score);//利用信号发送分数及难度数据给提示对话框
            n.exec();
        }else{//创造纪录
            endDialog e;
            connect(this,SIGNAL(infoSend(int,int)),&e,SLOT(infoRecv(int,int)));
            emit infoSend(level,score);//利用信号发送分数及难度数据给提示对话框
            e.exec();
        }
    }
}

//销毁屏幕上的方格
void game::deleteStar()
{
    for(int i=0;i<maxRow;i++)
        for(int j=0;j<maxColumn;j++)
            if(stars[i][j]!=NULL){
                delete stars[i][j];
                stars[i][j]=NULL;
            }
}

//刷新分数
void game::refreshScore()
{
    ui->timesLabel->setText(QString(tr("消除次数：%1")).arg(times));
    ui->scoreLabel->setText(QString(tr("分数：%1")).arg(score));
}

void game::startgame()
{
    this->show();
}

//处理从游戏开始界面接受到的数据
void game::infoRecv(const QString &type)
{
    if(type!=NULL){
        ui->nandulabel->setText(QString(tr("难度：%1")).arg(type));
        if(type == "简单") level = 1;
        else if(type == "中等") level = 2;
        else if(type == "复杂") level = 3;
        showStar();//生成方格
    }
}

//返回游戏开始界面
void game::on_gameBackBtn_clicked()
{
    deleteStar();
    sound->stop();
    this->hide();
    emit showmain();
}

//重新开始按钮
void game::on_newBtn_clicked()
{
    showStar();
}

//音乐播放按钮
void game::on_musicPushButton_clicked()
{
    isDoubleClicked++;//点击次数加1
   if(isDoubleClicked==1)//第一次点击后开始计时
       pQTimerDoubleClicked->start(430); //430ms为自己设置

   if(isDoubleClicked==2)//在所设时间内第二次点击，即双击
   {
       pQTimerDoubleClicked->stop();//停止定时器
       isDoubleClicked = 0; //初始化

       sound->stop();//停止播放
   }
}

//所设时间过完仍未进行第二次点击，定时器timeout()触发该槽函数
void game::timerSingleClick()
{
    pQTimerDoubleClicked->stop();//停止计时器
    isDoubleClicked = 0; //初始化

    sound->play();//播放
}
//void game::mouseMoveEvent(QMouseEvent* event)
// {
//    qDebug() << "cursor1";
//   QPoint mousepos = event->pos();

//     //在坐标（0 ~ width，0 ~ height）范围内改变鼠标形状
//    if(mousepos.rx() > minimumX && mousepos.rx() < minimumX+maxColumn*starSize
//            && mousepos.ry() > minimumY && mousepos.ry() < minimumY+maxRow*starSize)
//     {
//        qDebug() << "cursor2";
//            this->setCursor(*myCursor);
//     }
//     else
//     {
//         this->setCursor(Qt::ArrowCursor);      //范围之外变回原来形状
//     }
//}
//关闭窗口提示
void game::closeEvent( QCloseEvent * event )
{
    switch( QMessageBox::information( this, tr("game"),
  tr("Do you really want to quit game?"),
  tr("Yes"), tr("No") ) )
 {
    case 0:
        event->accept();
        break;
 default:
        event->ignore();
        break;
 }
}
