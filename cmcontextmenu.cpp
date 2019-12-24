#include "cmcontextmenu.h"

CommodityManagingContextMenu::CommodityManagingContextMenu(QTableView* parent):QMenu(parent)
{
    QAction *deleteAction = new QAction("删除");
    addAction(deleteAction);
}
