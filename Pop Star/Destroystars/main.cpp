#include "mainwindow.h"
#include <QApplication>
#include "connection.h"
#include <QProcess>
#include <QtGui>
#include <QFrame>
#include "game.h"
#include "enddialog.h"
#include "recorddialog.h"
#include <QDialog>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QProcess process;
    process.start("C:/MySQL/bin/mysqld.exe");

    if(!createConnection()) return 0;

    MainWindow w;
    w.show();

    game b;

    QObject::connect(&w,SIGNAL(showGame()),&b,SLOT(startgame()));       //页面跳转功能实现
    QObject::connect(&b,SIGNAL(showmain()),&w,SLOT(backhome()));        //页面跳转功能实现
    QObject::connect(&w,SIGNAL(infoSend(QString)),&b,SLOT(infoRecv(QString)));  //窗口跳转时传递数据

    return a.exec();
}
