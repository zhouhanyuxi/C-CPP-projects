#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFile"
#include "QStyleFactory"
#include "QPainter"
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QIcon>
#include <QEvent>
#include <QCloseEvent>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    setFixedSize(318,475);//固定窗口大小
    ui->tableView->setAlternatingRowColors(true);

    model = new QSqlTableModel(this);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);//设置编辑策略为提交才保存
    model->setTable("scores");
    model->select();
    ui->tableView->setModel(model);     //在tableview中显示记录
    QFile qssFile(":/myStyle/my_qss.qss"); //使用样式表
    qssFile.open(QFile::ReadOnly);// 只读方式打开该文件
    if(qssFile.isOpen())
    {
        QString qss = QLatin1String(qssFile.readAll());// 读取文件全部内容，使用tr()函数将其转换为QString类型
        qApp->setStyleSheet(qss);// 为QApplication设置样式表
        qssFile.close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


//帮助按钮
void MainWindow::on_HelpBtn_clicked()
{
    QFile data(":/myTxt/help.txt");
    if(!data.open(QFile::ReadOnly | QFile::Text))
        qDebug()<<"Can not open";//打开文件

    QTextStream in(&data);
    QString data1 = in.readAll();
    qDebug()<<data1;//确认文件是否读到
    QMessageBox message(QMessageBox::NoIcon,"帮助",data1);
    message.exec();
}


//分数按钮
void MainWindow::on_RecordBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    model->setTable("stars");
    model->setHeaderData(0, Qt::Horizontal,tr("难度"));   //设置表头数据
    model->setHeaderData(1, Qt::Horizontal,tr("姓名"));
    model->setHeaderData(2, Qt::Horizontal,tr("分数"));
    model->select();
}

//用户协议按钮
void MainWindow::on_agreementBtn_clicked()
{
    QFile data(":/myTxt/xieyi.txt");
    if(!data.open(QFile::ReadOnly | QFile::Text))
        qDebug()<<"Can not open";//打开文件

    QTextStream in(&data);
    QString data1 = in.readAll();
    qDebug()<<data1;//确认文件是否读到
    QMessageBox message(QMessageBox::NoIcon,"用户协议",data1);
    message.exec();
}

//开始游戏按钮
void MainWindow::on_startBtn_clicked()
{
    this->hide();
    emit showGame();        //发出显示游戏界面信号
    emit infoSend(ui->typecomboBox->currentText());     //传递难度等级数据
}

//回到主界面槽函数
void MainWindow::backhome()
{
    this->show();
}


//返回按钮返回主界面
void MainWindow::on_fanhuiBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

//关闭窗口提示
void MainWindow::closeEvent( QCloseEvent * event )
{
    switch( QMessageBox::information( this, tr("game"),
                tr("Do you really want to quit game?"),
                tr("Yes"), tr("No")) )
 {
    case 0:
        event->accept();
        break;
 default:
        event->ignore();
        break;
 }
}
