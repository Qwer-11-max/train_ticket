#ifndef triwindow_H
#define triwindow_H

#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QModelIndex>
#include <QList>
#include <QString>


namespace Ui {
class triwindow;
}

class triwindow : public QDialog
{
    Q_OBJECT

public:
    explicit triwindow(QWidget *parent = 0);
    ~triwindow();
    void sendShowSignal();
    QString getInitManagerAccount()const;
    QString getInitManagerPassword()const;

private:
    Ui::triwindow *ui;
    bool max;
    QRect location;
    QSqlTableModel *model;
    QModelIndex index;
    QList<QString> deletList;
    QString initManagerAccount;//tri
    QString initManagerPassword;//tri

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

    void on_addPushButton_2_clicked();

    void on_deletePushButton_2_clicked();

    void on_mannerComboBox_currentTextChanged(const QString &arg1);

    void on_searchPushButton_2_clicked();

    void on_showAll_clicked();

    void on_statisticPushButton_2_clicked();
};

#endif // triwindow_H
