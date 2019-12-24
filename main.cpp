#include "mainwindow.h"
#include <QApplication>
#include "sqlutil.h"

QSqlDatabase* SQLUtil::db = nullptr;
const QString SQLUtil::SHOW_TABLES = QString("show tables");
QSqlQuery* SQLUtil::query = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
