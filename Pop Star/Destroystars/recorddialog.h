#ifndef RECORDDIALOG_H
#define RECORDDIALOG_H

#include "enddialog.h"

namespace Ui {
class recordDialog;
}

class recordDialog : public endDialog
{
    Q_OBJECT

public:
    explicit recordDialog(QWidget *parent = 0);
    ~recordDialog();

private slots:

    void on_buttonBox_accepted();//ok按钮

private:
    Ui::recordDialog *ui;
};

#endif // RECORDDIALOG_H
