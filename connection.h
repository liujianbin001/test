#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("mystars.db");
    if (!db.open()) {
        QMessageBox::critical(0, "Cannot open database1","Unable to establish a database connection.", QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query;

  //   创建satllite表
    //query.exec("create table satllite (id int primary key, name varchar, a varchar, e varchar, i varchar, om varchar, w varchar, m0 varchar, perigee varchar, apogee varchar, period varchar, speada1 varchar, speada2 varchar, speada varchar)");
//    query.exec("insert into satllite values(1, 'ISS', 0,0,0,0,0,0,400200,0,0,30287,0,0)");

    // 创建SunMoon表
  //  query.exec("create table SunMoon (id int primary key, name varchar, a varchar, e varchar, i varchar, om varchar, w varchar, m0 varchar, perigee varchar, apogee varchar, period varchar, speada1 varchar, speada2 varchar, speada varchar)");
    //
//    query.exec("insert into SunMoon values(1, '水星', 57909100000,0.20563,0,0,0,0,147098074000,0,0,30287,0,0)");
//    query.exec("insert into SunMoon values(2, '金星', 0,0,0,0,0,0,147098074000,0,0,30287,0,0)");
//    query.exec("insert into SunMoon values(3, '地球', 0,0,0,0,0,0,147098074000,0,0,30287,0,0)");
//    query.exec("insert into SunMoon values(4, '火星', 0,0,0,0,0,0,147098074000,0,0,30287,0,0)");
//    query.exec("insert into SunMoon values(5, '木星', 0,0,0,0,0,0,147098074000,0,0,30287,0,0)");
//    query.exec("insert into SunMoon values(6, '土星', 0,0,0,0,0,0,147098074000,0,0,30287,0,0)");
//    query.exec("insert into SunMoon values(7, '天王星', 0,0,0,0,0,0,147098074000,0,0,30287,0,0)");
//    query.exec("insert into SunMoon values(8, '海王星', 0,0,0,0,0,0,147098074000,0,0,30287,0,0)");
//    query.exec("insert into SunMoon values(9, '冥王星', 0,0,0,0,0,0,147098074000,0,0,30287,0,0)");

    return true;
}

#endif // CONNECTION_H
