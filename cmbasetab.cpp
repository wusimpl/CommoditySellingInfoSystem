#include "cmbasetab.h"
#include "ui_cmbasetab.h"


CmBaseTab::CmBaseTab(QString tableName) :
    QWidget(nullptr),
    ui(new Ui::BaseTab)
{
    ui->setupUi(this);

    tableView = new CustomTableView(tableName);
    ui->verticalLayout->addWidget(tableView);

    //初始化queryTypeCombox
    QSqlTableModel* model = tableView->getModel();
    for (int i=0;i<model->columnCount();i++) {
        QString columnName = model->headerData(i,Qt::Horizontal).toString();
        ui->queryTypeCombox->addItem(columnName);
    }
}

CmBaseTab::~CmBaseTab()
{
    delete ui;
}

void CmBaseTab::on_submitActionButton_clicked()
{
    tableView->getModel()->submitAll();

}

void CmBaseTab::on_revokeActionButton_clicked()
{
    tableView->getModel()->revert();
    tableView->getModel()->select();//刷新视图
}

void CmBaseTab::on_queryEdit_textChanged(const QString &queryText)
{
    QString queryType = ui->queryTypeCombox->currentText();

    QString filterStr = QString("%1 like '%%2%'").arg(queryType).arg(queryText);
    qDebug()<<filterStr;
    tableView->getModel()->setFilter(filterStr);
    tableView->getModel()->select();
}
