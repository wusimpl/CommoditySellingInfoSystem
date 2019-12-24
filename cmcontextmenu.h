#ifndef COMMODITYMANAGINGCONTEXTMENU_H
#define COMMODITYMANAGINGCONTEXTMENU_H
#include <QWidget>
#include <QMenu>
#include <QTableView>

class CommodityManagingContextMenu:public QMenu
{
    Q_OBJECT
public:
    CommodityManagingContextMenu(QTableView* parent);
};

#endif // COMMODITYMANAGINGCONTEXTMENU_H
