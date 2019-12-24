#include "customtableview.h"


CustomTableView::CustomTableView(QString tableName)
{
    connect(this,
            SIGNAL(customContextMenuRequested(QPoint)),
            this,
            SLOT(onRightClickMenu(QPoint)));//绑定上下文菜单

    this->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中
    this->setContextMenuPolicy(Qt::CustomContextMenu);//右键菜单自定义

    //设置列宽自适应
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    setupModels(tableName);
}


void CustomTableView::setupModels(QString tableName){
    //set model
    if(tableName.compare("order") == 0){
        model = new QSqlTableModel (this);
    }else{
        model = new QSqlRelationalTableModel(this);
    }
    model->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);//手动提交
    model->setTable(tableName);
    this->setModel(model);
    model->select();//获取数据
}


void CustomTableView::onRightClickMenu(QPoint pos)
{
    auto index = this->indexAt(pos);
    if (index.isValid())
    {
        CommodityManagingContextMenu menu(this);
        menu.exec(QCursor::pos()); // 菜单出现的位置为当前鼠标的位置
    }
}


QSqlTableModel *CustomTableView::getModel() const
{
    return model;
}
