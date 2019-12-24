#ifndef COMMODITYMANAGINGCONTEXTMENU_H
#define COMMODITYMANAGINGCONTEXTMENU_H
#include <QWidget>
#include <QMenu>
#include <QTableView>
#include <QSqlRelationalTableModel>

class CommodityManagingContextMenu:public QMenu
{
    Q_OBJECT
public:
    CommodityManagingContextMenu(QTableView* parent);

public slots:
    void deleteCurrentRow();
};

#endif // COMMODITYMANAGINGCONTEXTMENU_H
