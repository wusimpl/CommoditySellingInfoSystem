#ifndef SELLINGPAGE_H
#define SELLINGPAGE_H

#include <QWidget>
#include <QStandardItemModel>
#include <QSqlQuery>

namespace Ui {
class SellingPage;
}

class SellingPage : public QWidget
{
    Q_OBJECT

public:
    explicit SellingPage(QWidget *parent = nullptr);
    ~SellingPage();

private slots:
    void on_AddToCartButton_clicked();

    void on_SupplierComboBox_currentIndexChanged(int index);

    void on_CommodityComboBox_currentIndexChanged(int index);

    void on_PlaceOrderButton_clicked();

private:
    Ui::SellingPage *ui;

    QStandardItemModel* model = nullptr;

    void setModels();
    void setViews();
};

#endif // SELLINGPAGE_H
