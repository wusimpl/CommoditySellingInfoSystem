#ifndef CSPAGE_H
#define CSPAGE_H

#include <QWidget>
#include <QAbstractItemModel>
#include <QAbstractItemView>
#include <QTableView>
#include <QSplitter>
#include "pieview.h"
#include <QSqlTableModel>
#include <QHeaderView>
#include <QGridLayout>
#include "customtableview.h"
#include <QStandardItemModel>
#include <QTime>

namespace Ui {
class CsPage;
}

//commodity statistics page
class CsPage : public QWidget
{
    Q_OBJECT

public:
    explicit CsPage(QWidget *parent = nullptr);
    ~CsPage();

    void setupViews();
    void setupModel();
    void setupDatas();
private:
    Ui::CsPage *ui;

    QAbstractItemModel *model = nullptr;
    QAbstractItemView *pieChart = nullptr;
};

class ColorGen
{
    QVector<QColor> used;//标记已经使用过的颜色
    ulong limit; //最多可以生成limit个颜色
public:
    ColorGen(ulong lim) : limit(lim){}

    QColor operator()()
    {
        int sz = used.size();
        while (sz < static_cast<int>(limit))
        {
            QColor clr(qrand() % 256, qrand() % 256, qrand() % 256);
            if (!used.contains(clr))
            {
                used.append(clr);
                return clr;
            }
        }
        //如果颜色已经完全用完，则将所有颜色清空
        used.clear();
        return QColor();
    }
};

#endif // CSPAGE_H
