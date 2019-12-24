#include "cspage.h"
#include "ui_cspage.h"

CsPage::CsPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CsPage)
{
    ui->setupUi(this);

    QGridLayout* layout = new QGridLayout(this);
    this->setLayout(layout);

    setupModel();
    setupViews();
    setupDatas();

}

CsPage::~CsPage()
{
    delete ui;
}

void CsPage::setupModel()
{

    model = new QStandardItemModel(0,2,this);
    model->setHeaderData(0, Qt::Horizontal, tr("供应商"));
    model->setHeaderData(1, Qt::Horizontal, tr("商品种类数"));
}

void CsPage::setupViews()
{
    QSplitter *splitter = new QSplitter;
    QTableView *table = new QTableView;
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);//不可编辑
    table->resizeRowsToContents();//根据内容自动调整行高
    pieChart = new PieView;

    //设置列宽铺满自适应
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //设置行高内容自适应
    table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    splitter->addWidget(table);
    splitter->addWidget(pieChart);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);

    table->setModel(model);
    pieChart->setModel(model);
    QItemSelectionModel *selectionModel = new QItemSelectionModel(model);
    table->setSelectionModel(selectionModel);
    pieChart->setSelectionModel(selectionModel);

    table->horizontalHeader()->setStretchLastSection(true);

    this->layout()->addWidget(splitter);
//    setCentralWidget(splitter);
}

void CsPage::setupDatas(){
    QSqlQuery query;
    query.exec("select supplier_name,count(commodity.commodity_name) as 商品种类数\
               from supply,commodity\
               where supply.commodity_code = commodity.commodity_code\
               group by supplier_name;");

    ColorGen colorGen(100);
    int row = 0;
    while (query.next()) {
        model->insertRow(row);
        model->setData(model->index(row, 0, QModelIndex()),query.value(0).toString());
        model->setData(model->index(row, 1, QModelIndex()),query.value(1).toInt());
        model->setData(model->index(row, 0, QModelIndex()),
                      QColor(colorGen()),
                       Qt::DecorationRole);
        row++;
    }
}
