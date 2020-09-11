#include "enddialog.h"
#include "ui_enddialog.h"
#include "QPainter"
endDialog::endDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::endDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(495,371);
    dialogScore = 0;        //初始化分数
    type = "";              //
}

endDialog::~endDialog()
{
    delete ui;
}

//处理接受到的数据
void endDialog::infoRecv(int level,int score)
{
    dialogScore = score;
    if(level == 1)type = "简单";
    if(level == 2)type = "中等";
    if(level == 3)type = "复杂";
    ui->label->setText(QString(tr("难度：%1")).arg(type));
    ui->label_2->setText(QString(tr("分数：%1")).arg(dialogScore));
}
void endDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    // 从窗口左上角开始绘制图片
    painter.drawPixmap(0,0,QPixmap(":/star/images/enddialog.jpg"));
    painter.fillRect(rect(),QColor(255,255,255,100));
}
