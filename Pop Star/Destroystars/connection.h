#ifndef CONNECTION_H
#define CONNECTION_H
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>


static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("mydata");
    db.setUserName("root");
    db.setPassword("");
    if (!db.open()) {
        QMessageBox::critical(0, QObject::tr("无法打开数据库"), "无法创建数据库连接！", QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query;
    // 使数据库支持中文
    query.exec("SET NAMES 'Latin1'");
    // 创建最高记录表
    query.exec("create table stars(type varchar(20) primary key,name varchar(40),scores int)");
    query.exec("insert into stars values('easy','nobody',0)");
    query.exec("insert into stars values('middle','nobody',0)");
    query.exec("insert into stars values('sophisticated','nobody',0)");

    return true;
}
#endif // CONNECTION_H
