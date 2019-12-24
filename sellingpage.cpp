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

    //加载供应商数据
    QSqlQuery query;
    QString querySupplierDataStr = "select supplier_name from supplier;";
    query.exec(querySupplierDataStr);

    int row = 0;
    while (query.next()) {
        ui->SupplierComboBox->addItem(query.value(0).toString());
        row++;
    }
}

//添加到购物车
void SellingPage::on_AddToCartButton_clicked()
{

}

//下订单
void SellingPage::on_PlaceOrderButton_clicked()
{

}

//供应商改变,加载商品数据
void SellingPage::on_SupplierComboBox_currentIndexChanged(int index)
{

}

//商品改变，更新商品详细数据
void SellingPage::on_CommodityComboBox_currentIndexChanged(int index)
{

}
