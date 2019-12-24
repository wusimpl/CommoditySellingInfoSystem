#ifndef SELLINGPAGE_H
#define SELLINGPAGE_H

#include <QWidget>
#include <QStandardItemModel>
#include <QSqlQuery>
#include <QList>
#include <QDateTime>
#include "sqlutil.h"

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

    void on_SupplierComboBox_currentIndexChanged(QString supplierName);

    void on_CommodityComboBox_currentIndexChanged(QString commoditysName);

    void on_PlaceOrderButton_clicked();

    void on_QuantityText_textChanged(const QString &arg1);

    int getMaxOrderCode();
    QString getCurrentTime();
    void clearCustomerOrderInfo();
    void clearCart();

private:
    Ui::SellingPage *ui;

    QStandardItemModel* model = nullptr;

    void setModels();
    void setViews();
};

#endif // SELLINGPAGE_H
