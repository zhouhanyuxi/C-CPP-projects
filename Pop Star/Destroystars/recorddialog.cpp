#include "recorddialog.h"
#include "ui_recorddialog.h"
#include <QSqlQuery>
#include <QMessageBox>

recordDialog::recordDialog(QWidget *parent) :
    endDialog(parent),
    ui(new Ui::recordDialog)
{
    ui->setupUi(this);
    setFixedSize(495,371);
    ui->lineEdit->setMaxLength(20);
    ui->lineEdit->setText("nobody");
}

recordDialog::~recordDialog()
{
    delete ui;
}

//对话框OK按钮
void recordDialog::on_buttonBox_accepted()
{
    QString name;
    if(ui->lineEdit->text() != ""){
        name = ui->lineEdit->text();
    }else{
        name = "nobody";
    }
    if(type == "简单")type = "easy";
    if(type == "中等")type = "middle";
    if(type == "复杂")type = "sophisticated";

    //保存最高纪录
    QSqlQuery query;
    QSqlDatabase::database().transaction(); // 事务操作
    bool rtn = query.exec(QString("update stars set name = '%1',scores = %2 where type = '%3'")
               .arg(name).arg(dialogScore).arg(type));
    if(rtn){
        QSqlDatabase::database().commit();
        QMessageBox::information(this,tr("提示"),tr("保存成功！"),QMessageBox::Ok);
    }else{
        QSqlDatabase::database().rollback();
        QMessageBox::information(this,tr("提示"),tr("保存失败，无法访问数据库！"),QMessageBox::Ok);
    }

}
