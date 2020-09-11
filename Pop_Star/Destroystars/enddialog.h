#ifndef ENDDIALOG_H
#define ENDDIALOG_H

#include <QDialog>

namespace Ui {
class endDialog;
}

class endDialog : public QDialog
{
    Q_OBJECT

public:
    explicit endDialog(QWidget *parent = 0);
    ~endDialog();

private:
    Ui::endDialog *ui;
    void paintEvent(QPaintEvent *);
protected:
    QString type;//难度
    int dialogScore;//分数
private slots:
    void infoRecv(int,int);//接受数据

};

#endif // ENDDIALOG_H
