#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sqlutil.h"
#include "customtableview.h"
#include <QSqlTableModel>
#include<QHeaderView>
#include <QLayoutItem>
#include "cmcontextmenu.h"
#include "cmbasetab.h"
#include "cspage.h"
#include "sellingpage.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void selfInit();
    void dataInit();
    void addOneTabByTableName(QString tableName);

//菜单栏响应
private slots:
    //销售页面
    void on_SellingAction_triggered();
    //商品等表的管理界面
    void on_CMAction_triggered();
    //商品统计页面
    void on_CSAction_triggered();
    //销售统计页面
    void on_SSAction_triggered();

private:
    Ui::MainWindow *ui;
    QWidget** pages;//页面
};

#endif // MAINWINDOW_H
