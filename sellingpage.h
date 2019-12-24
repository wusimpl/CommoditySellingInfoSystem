#ifndef SELLINGPAGE_H
#define SELLINGPAGE_H

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
class SellingPage;
}

class SellingPage : public QWidget
{
    Q_OBJECT

public:
    explicit SellingPage(QWidget *parent = nullptr);
    ~SellingPage();

private:
    Ui::SellingPage *ui;

    QStandardItemModel* model = nullptr;

    void setModels();
    void setViews();
};

#endif // SELLINGPAGE_H
