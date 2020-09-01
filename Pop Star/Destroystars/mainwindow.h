#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QSqlTableModel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
   // void actionOpenSlot();

    void closeEvent( QCloseEvent * event );//关闭窗口提示
private slots:

    void on_HelpBtn_clicked();      //帮助按键

    void on_RecordBtn_clicked();    //分数记录按键

    void on_agreementBtn_clicked(); //用户协议按键

    void on_startBtn_clicked();     //开始游戏按键

    void backhome();                //返回主界面槽函数

    void on_fanhuiBtn_clicked();    //返回按键


private:
    Ui::MainWindow *ui;

    QSqlTableModel *model;
signals:
    void showGame();                //定义游戏界面信号
    void infoSend(const QString &); //定义消息发送信号
};

#endif // MAINWINDOW_H
