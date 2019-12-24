#ifndef CUSTOMTABLEVIEW_H
#define CUSTOMTABLEVIEW_H
#include <QTableView>
#include "cmcontextmenu.h"
#include <QSqlRelationalTableModel>
#include <QHeaderView>
#include "sqlutil.h"
#include <QDebug>
#include <QSqlRelationalTableModel>

class CustomTableView : public QTableView
{
    Q_OBJECT
public:
    CustomTableView(QString tableName);

    QSqlTableModel *getModel() const;

    void setupModels(QString tableName);
public slots:
    void onRightClickMenu(QPoint pos);

private:
    QSqlTableModel* model;
};

#endif // CUSTOMTABLEVIEW_H
