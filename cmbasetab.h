#ifndef BASETAB_H
#define BASETAB_H

#include <QWidget>
#include "customtableview.h"

namespace Ui {
class BaseTab;
}
//CommodityManagment BaseTab
class CmBaseTab : public QWidget
{
    Q_OBJECT

public:
    explicit CmBaseTab(QString tableName);
    ~CmBaseTab();

private slots:
    void on_submitActionButton_clicked();

    void on_revokeActionButton_clicked();

    void on_queryEdit_textChanged(const QString &arg1);

private:
    Ui::BaseTab *ui;

     CustomTableView *tableView ;
};

#endif // BASETAB_H
