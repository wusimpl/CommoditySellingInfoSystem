#ifndef SQLUTIL_H
#define SQLUTIL_H
#include <QtSql/QSqlDatabase>
#include <QWidget>
#include <QtSql/QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>

class SQLUtil
{
private:
    static QSqlDatabase* db;
public:
    static void connectDB(QWidget* parent);

    static QSqlDatabase *getDb();

    static QSqlQuery* query;

    const static QString SHOW_TABLES;
};

#endif // SQLUTIL_H
