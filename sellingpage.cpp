#include "sellingpage.h"
#include "ui_sellingpage.h"
#include <QDebug>

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
    model->setHeaderData(2, Qt::Horizontal, tr("单价(元)"));
    model->setHeaderData(3, Qt::Horizontal, tr("数量"));
    model->setHeaderData(4, Qt::Horizontal, tr("总计(元)"));


}

void SellingPage::setViews()
{

    ui->QuantityText->setValidator(new QIntValidator(0, 1000, this)); //限制为只能输入数字

    //设置列宽铺满自适应
    ui->CartTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //设置行高内容自适应
    ui->CartTableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->CartTableView->setModel(model);
    ui->CartTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//不允许编辑

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
    //数量为空
    if(ui->QuantityText->text().compare("") == 0){
        return;
    }

    QStandardItemModel *model = static_cast<QStandardItemModel*>(ui->CartTableView->model());
    QList<QStandardItem*> singleCommodityInfo;
    singleCommodityInfo.append(new QStandardItem (ui->SupplierComboBox->currentText()));
    singleCommodityInfo.append(new QStandardItem (ui->CommodityComboBox->currentText()));
    singleCommodityInfo.append(new QStandardItem (ui->PriceLabel->text()));
    singleCommodityInfo.append(new QStandardItem (ui->QuantityText->text()));
    float totalPrice = ui->PriceLabel->text().toFloat()*ui->QuantityText->text().toFloat();
    singleCommodityInfo.append(new QStandardItem(QString("%1").arg(static_cast<double>(totalPrice))));
    model->appendRow(singleCommodityInfo);
}

//下订单
void SellingPage::on_PlaceOrderButton_clicked()
{
    QStandardItemModel *model = static_cast<QStandardItemModel*>(ui->CartTableView->model());

    //订单信息
    int orderCode = getMaxOrderCode()+1;
    QString customerName = ui->CustomerNameText->text();
    QString tel = ui->TelText->text();
    QString address = ui->AddressText->text();
    QString postCode = ui->PostCodeText->text();
    QString currentTime = getCurrentTime();
    QSqlQuery orderQuery;
    QString insertOrderRecordStr = QString("insert into `order` "
                                           "values(%1,'%2','%3','%4','%5','%6');")
            .arg(orderCode)
            .arg(customerName)
            .arg(tel)
            .arg(address)
            .arg(postCode)
            .arg(currentTime);
    //写入订单信息
    orderQuery.exec(insertOrderRecordStr);

    //订单详细信息
//    QList<QStandardItem*> singleCommodityInfo;
    QSqlQuery orderDetailQuery;
    orderDetailQuery.prepare("insert into order_detail"
                             "(order_code,commodity_code,unit_price,purchase_quantity) "
                             "values(?,?,?,?);");

    for (int i = 0;i<model->rowCount();i++) {
//        singleCommodityInfo = model->takeRow(i);
        //订单代码外键
        orderDetailQuery.addBindValue(orderCode);
        //商品代码
        QString commodityName = model->index(i,1).data().toString();
        QString commodityCode;
        QSqlQuery commodityCodeQuery;//通过商品名获取商品代码
        commodityCodeQuery.exec(QString("select commodity_code from commodity "
                                        "where commodity_name='%1'")
                                .arg(commodityName));
        while (commodityCodeQuery.next()) {
            commodityCode = commodityCodeQuery.value(0).toString();
            break;
        }
        orderDetailQuery.addBindValue(commodityCode);
        //单价
        float unit_price = model->index(i,2).data().toFloat();
        orderDetailQuery.addBindValue(unit_price);
        //数量
        int purchase_quantity = model->index(i,3).data().toInt();
        orderDetailQuery.addBindValue(purchase_quantity);

        //写入订单详情
        orderDetailQuery.exec();
    }

    clearCart();
    clearCustomerOrderInfo();

     QMessageBox msgBox;
     msgBox.setParent(this);
     msgBox.setText("购买成功!");
     msgBox.exec();

}



//供应商改变,加载商品数据
void SellingPage::on_SupplierComboBox_currentIndexChanged(QString supplierName)
{
    ui->PriceLabel->clear();
    ui->QuantityText->clear();
    //加载商品数据
    QSqlQuery query;
    QString queryCommodityDataStr = QString("select commodity.commodity_code,commodity.commodity_name from commodity,supply "
                                    "where supply.supplier_name='%1' "
                                    "and "
                                    "commodity.commodity_code = supply.commodity_code;").arg(supplierName);
    query.exec(queryCommodityDataStr);


    ui->CommodityComboBox->clear();//清空

    //写入comboBox
    int row = 0;
    while (query.next()) {
        ui->CommodityComboBox->addItem(query.value(1).toString(),
                                       query.value(0).toString());
        row++;
    }
}

//商品改变，更新商品详细数据
void SellingPage::on_CommodityComboBox_currentIndexChanged(QString commodityName)
{
    Q_UNUSED(commodityName);

    QString currentCommodityCode = ui->CommodityComboBox->currentData().toString();

    //加载商品详细数据
    QSqlQuery query;
    QString queryCommodityPriceStr = QString("select marketing_price from commodity "//一定要有空格了
                                            "where commodity_code = '%1'").arg(currentCommodityCode);
//    qDebug()<<queryCommodityPriceStr;
    query.exec(queryCommodityPriceStr);

    //写入comboBox
    while (query.next()) {
       ui->PriceLabel->setText(query.value(0).toString());
       break;
    }

    ui->QuantityText->setText("1");
}

//库存校验
void SellingPage::on_QuantityText_textChanged(const QString &wantedQuantity)
{
    QString currentCommodityCode = ui->CommodityComboBox->currentData().toString();

    //加载商品详细数据
    QSqlQuery query;
    QString queryCommodityStockQuantityStr = QString("select stock_quantity from commodity "//一定要有空格了
                                            "where commodity_code = '%1'").arg(currentCommodityCode);
    query.exec(queryCommodityStockQuantityStr);

    int stockQuantity = 0;
    //写入comboBox
    while (query.next()) {
       stockQuantity = query.value(0).toInt();
       break;
    }

    if(wantedQuantity.toInt()>stockQuantity){
        ui->TipsLabel->setText(tr("超过了库存数量!"));
        ui->AddToCartButton->setEnabled(false);
    }else{
        ui->TipsLabel->setText(tr(""));
        ui->AddToCartButton->setEnabled(true);
    }
}

//得到最大的订单编号
int SellingPage::getMaxOrderCode()
{
    int maxOrderCode = 1;
    QSqlQuery query;
    query.exec("select max(order_code) from `order`");
    while (query.next()) {
        maxOrderCode = query.value(0).toInt();
        break;
    }
    return maxOrderCode;
}

QString SellingPage::getCurrentTime()
{
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString currentTime = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");//获取当前时间
    return currentTime;
}

void SellingPage::clearCustomerOrderInfo()
{
    ui->CustomerNameText->clear();
    ui->TelText->clear();
    ui->AddressText->clear();
    ui->PostCodeText->clear();
}

void SellingPage::clearCart()
{
    int row = ui->CartTableView->model()->rowCount();
    for (int i=0; i<row; i++)
    {
        ui->CartTableView->model()->removeRow(0);
    }
}
