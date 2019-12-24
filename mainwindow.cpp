#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    selfInit();
    dataInit();

    //初始化页面
    pages = new QWidget*[4];
    for (QWidget** page = &pages[0];page < &pages[4];page++) {
        *page = nullptr;
    }
    *pages = ui->StackedWidget->widget(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::selfInit()
{
    ui->setupUi(this);
    this->setWindowTitle("商品销售管理系统");

    ui->CommodityManagingTabWidget->removeTab(0);
    ui->CommodityManagingTabWidget->removeTab(0);
}

void MainWindow::dataInit()
{
     SQLUtil::connectDB(this);//连接数据库
     if(SQLUtil::getDb() == nullptr){
         return;
     }

     //查询数据库中的所有表，每个表对应一个tab页面
     SQLUtil::query = new QSqlQuery();
     SQLUtil::query->exec(SQLUtil::SHOW_TABLES);
     while(SQLUtil::query->next()){
        QString tableName = SQLUtil::query->value(0).toString();

        addOneTabByTableName(tableName);
     }
}

void MainWindow::addOneTabByTableName(QString tableName)
{
    //一个tab对应一个表及其操作
    CmBaseTab* currentTab = new CmBaseTab(tableName);

    ui->CommodityManagingTabWidget->addTab(currentTab,tableName);
}


//商品管理页面
void MainWindow::on_CMAction_triggered()
{
    ui->StackedWidget->setCurrentWidget(pages[0]);
}

void MainWindow::on_CSAction_triggered()
{
    if(pages[1] == nullptr){
        pages[1] = new CsPage();
        ui->StackedWidget->addWidget(pages[1]);
    }
    ui->StackedWidget->setCurrentWidget(pages[1]);
}

void MainWindow::on_SellingAction_triggered()
{
    if(pages[2] == nullptr){
        pages[2] = new SellingPage();
        ui->StackedWidget->addWidget(pages[2]);
    }
    ui->StackedWidget->setCurrentWidget(pages[2]);
}

void MainWindow::on_SSAction_triggered()
{
    if(pages[2] == nullptr){
        pages[2] = new CsPage();
        ui->StackedWidget->addWidget(pages[2]);
    }
    ui->StackedWidget->setCurrentWidget(pages[2]);
}
