#include "sqlutil.h"


QSqlDatabase *SQLUtil::getDb()
{
    if(db->isOpen())
        return db;
    else {
        return nullptr;
    }
}

void SQLUtil::connectDB(QWidget* parent)
{
    if(db != nullptr && db->isOpen()){
        return;
    }
    QSqlDatabase tempDb = QSqlDatabase::addDatabase("QMYSQL");
    SQLUtil::db = &tempDb;
    SQLUtil::db->setPort(3306);
    SQLUtil::db->setHostName("localhost");
    SQLUtil::db->setUserName("root");
    SQLUtil::db->setPassword("Wxp13620060844.");

    SQLUtil::db->setDatabaseName("CSIS");

    if(!SQLUtil::db->open()){
        QMessageBox::warning(parent,"错误","数据库连接错误!"+db->lastError().text());
        SQLUtil::db = nullptr;
    }else{
        qDebug()<<"数据库连接成功!";
    }
}

QString SQLUtil::lastError(){
    return db->lastError().text();
}
