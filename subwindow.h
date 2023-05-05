#ifndef subwindow_H
#define subwindow_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QModelIndex>
#include "confirmrefund.h"
#include "journey.h"
#include "passenger.h"

namespace Ui {
class subwindow;
}

class subwindow : public QDialog
{
    Q_OBJECT

public:
    explicit subwindow(QWidget *parent = 0);
    ~subwindow();
    void sendShowSignal();
    void setPassengerText();
    void confirmDelete();
    void nConfirmDelete();
    QSqlTableModel *getModel();
    passenger& getNowPassenger();

private:
    Ui::subwindow *ui;
    bool max;
    QRect location;
    passenger nowPassenger;
    QSqlTableModel *model;//一个数据库表可视化模型
    confirmRefund *confirm;
    QModelIndex index;

signals:
    void showForm();

private slots:
    void initForm();
    void initIndex();
    void currentItemChanged(int, const QString &item);

private slots:
    void on_btnMenu_Min_clicked();

    void on_btnMenu_Max_clicked();

    void on_btnMenu_Close_clicked();

    void on_startProvince_currentTextChanged(const QString &arg1);

    void on_endProvince_currentTextChanged(const QString &arg1);

    void on_purchaseButton_clicked(bool checked);

    void on_priceShowButton_clicked(bool checked);

    void on_refundButton_clicked(bool checked);

    void on_submitPushButton_clicked();

    void on_CancelPushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);
};

#endif // subwindow_H
