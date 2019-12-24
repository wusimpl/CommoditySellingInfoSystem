#include "sellingpage.h"
#include "ui_sellingpage.h"

SellingPage::SellingPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SellingPage)
{
    ui->setupUi(this);

    setModels();
    setViews();

}

SellingPage::~SellingPage()
{
    delete ui;
}

void SellingPage::setModels()
{
    model = new QStandardItemModel(0,5,this);
    model->setHeaderData(0, Qt::Horizontal, tr("供应商"));
    model->setHeaderData(1, Qt::Horizontal, tr("商品"));
    model->setHeaderData(2, Qt::Horizontal, tr("单价"));
    model->setHeaderData(3, Qt::Horizontal, tr("数量"));
    model->setHeaderData(4, Qt::Horizontal, tr("总计"));


}

void SellingPage::setViews()
{
    //设置列宽铺满自适应
    ui->CartTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //设置行高内容自适应
    ui->CartTableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->CartTableView->setModel(model);
}
