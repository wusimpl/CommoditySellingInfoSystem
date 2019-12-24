#include "cmcontextmenu.h"
#include <QDebug>

CommodityManagingContextMenu::CommodityManagingContextMenu(QTableView* parent):QMenu(parent)
{
    QAction *deleteAction = new QAction("删除");
    connect(deleteAction,SIGNAL(triggered()),this,SLOT(deleteCurrentRow()));
    addAction(deleteAction);
}

void CommodityManagingContextMenu::deleteCurrentRow()
{
    QTableView* parentTableView = static_cast<QTableView*>(this->parent());
    QModelIndex currentModelIndex = parentTableView->currentIndex();
    int currentModelRow = currentModelIndex.row();
    qDebug()<<currentModelRow;
    QSqlRelationalTableModel* model = static_cast<QSqlRelationalTableModel*>(parentTableView->model());
    model->removeRow(currentModelRow);
}

