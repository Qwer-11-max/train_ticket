#include "subwindow.h"
#include "ui_subwindow.h"
#include "sliderbar.h"
#include "iconhelper.h"
#include "qtimer.h"

subwindow::subwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::subwindow)
{
    ui->setupUi(this);
    this->initForm();
    int frmX = this->width();
    int frmY = this->height();
    QRect screenRect = QGuiApplication::primaryScreen()->geometry();
    int deskWidth = screenRect.width();
    int deskHeight = screenRect.height();
    QPoint movePoint(deskWidth / 2 - frmX / 2, deskHeight / 2 - frmY / 2);
    this->move(movePoint);
    QTimer::singleShot(100, this, SLOT(initIndex()));

    setWindowTitle("乘客端");
    this->confirm=new confirmRefund();
    ui->numberSpinBox->setMinimum(1);
    ui->numberSpinBox->setMaximum(5);
    this->model = new QSqlTableModel(this);//一个数据库表可视化模型
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);   // 设置编辑策略为手动提交
    model->setTable("journey");
    model->setHeaderData(0, Qt::Orientation::Horizontal, "票号");
    model->setHeaderData(1, Qt::Orientation::Horizontal, "身份证号");
    model->setHeaderData(2, Qt::Orientation::Horizontal, "姓名");
    model->setHeaderData(3, Qt::Orientation::Horizontal, "始发省份");
    model->setHeaderData(4, Qt::Orientation::Horizontal, "始发城市");
    model->setHeaderData(5, Qt::Orientation::Horizontal, "终点省份");
    model->setHeaderData(6, Qt::Orientation::Horizontal, "终点城市");
    model->setHeaderData(7, Qt::Orientation::Horizontal, "席别");
    model->setHeaderData(8, Qt::Orientation::Horizontal, "始发时间");
    model->setHeaderData(9, Qt::Orientation::Horizontal, "价格");
    model->setHeaderData(10, Qt::Orientation::Horizontal, "购票时间");
    model->select();//显示数据库表
    ui->tableView->setModel(model);//显示模型的位置
    connect(this->confirm,this->confirm->confirm,this,this->confirmDelete);
    connect(this->confirm,this->confirm->nconfirm,this,this->nConfirmDelete);
    ui->stackedWidget->setCurrentIndex(0);
}

subwindow::~subwindow()
{
    delete ui;
}

void subwindow::initForm()
{
    this->max = false;
    this->location = this->geometry();
    this->setProperty("form", true);
    this->setProperty("canMove", true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

    this->setWindowTitle("火车订票系统");

    IconHelper::Instance()->setIcon(ui->labTitle, QChar(0xf238), 35);
    IconHelper::Instance()->setIcon(ui->btnMenu_Min, QChar(0xF068));
    IconHelper::Instance()->setIcon(ui->btnMenu_Max, QChar(0xF067));
    IconHelper::Instance()->setIcon(ui->btnMenu_Close, QChar(0xF00d));

    QStringList qss;
    qss.append("QLabel#labTitle{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 #2AA2DA, stop:1 #12B5C9);color:#F0F0F0;}");
    qss.append("QWidget#widgetTop{background:#FFFFFF;}");
    qss.append("QWidget#widgetMain{background:#F1F3F6;}");
    qss.append("QLabel#label{color:#202020;font:50pt;}");
    this->setStyleSheet(qss.join(""));

    QString items = "购票;退票;改签;退出";
    ui->widgetNavLeft->setItems(items);
    ui->widgetNavLeft->setHorizontal(false);
    ui->widgetNavLeft->setLineWidth(5);
    ui->widgetNavLeft->setLineColor(QColor("#029FEA"));
    ui->widgetNavLeft->setBgColorStart(QColor("#292F38"));
    ui->widgetNavLeft->setBgColorEnd(QColor("#292F38"));
    ui->widgetNavLeft->setBarColorStart(QColor("#1D2025"));
    ui->widgetNavLeft->setBarColorEnd(QColor("#1D2025"));
    ui->widgetNavLeft->setTextNormalColor(QColor("#54626F"));
    ui->widgetNavLeft->setTextSelectColor(QColor("#FDFDFD"));
    ui->widgetNavLeft->setBarStyle(SliderBar::BarStyle_Line_Left);

    ui->widgetNavTop->setHorizontal(true);
    ui->widgetNavTop->setLineWidth(5);
    ui->widgetNavTop->setSpace(100);
    ui->widgetNavTop->setLineColor(QColor("#1CA0E4"));
    ui->widgetNavTop->setBgColorStart(QColor("#FFFFFF"));
    ui->widgetNavTop->setBgColorEnd(QColor("#FFFFFF"));
    ui->widgetNavTop->setBarColorStart(QColor("#FAFBFD"));
    ui->widgetNavTop->setBarColorEnd(QColor("#FAFBFD"));
    ui->widgetNavTop->setTextNormalColor(QColor("#6D7173"));
    ui->widgetNavTop->setTextSelectColor(QColor("#6D7173"));
    ui->widgetNavTop->setBarStyle(SliderBar::BarStyle_Line_Bottom);

    connect(ui->widgetNavLeft, SIGNAL(currentItemChanged(int, QString)),
            this, SLOT(currentItemChanged(int, QString)));
    connect(ui->widgetNavTop, SIGNAL(currentItemChanged(int, QString)),
            this, SLOT(currentItemChanged(int, QString)));
}

void subwindow::initIndex()
{
    ui->widgetNavLeft->setCurrentIndex(0);
}

void subwindow::currentItemChanged(int i , const QString &item)
{
    ui->stackedWidget->setCurrentIndex(i);
    if(i==2)
        QMessageBox::information(this,"操作提示","请先在列表中选取您要修改的始发时间\n再在日历中选择您要改签的时间",QMessageBox::Ok);
    else if (i == 3)
        this->sendShowSignal();
}

void subwindow::on_btnMenu_Min_clicked()
{
    showMinimized();
}

void subwindow::on_btnMenu_Max_clicked()
{
    if (max) {
        this->setGeometry(location);
        this->setProperty("canMove", true);
    } else {
        location = this->geometry();
        this->setGeometry(qApp->screens()[0]->availableGeometry());
        this->setProperty("canMove", false);
    }

    max = !max;
}

void subwindow::on_btnMenu_Close_clicked()
{
    close();
}

void subwindow::sendShowSignal()
{
    emit showForm();
}

void subwindow::setPassengerText()
{
    ui->nameShow->setText(this->nowPassenger.getName());
    ui->idShow->setText(this->nowPassenger.getId());
}

void subwindow::confirmDelete()
{
    QString number=ui->refundLineEdit->text();
    QString sql=QString("delete from journey where tid='%1'").arg(number);
    QSqlDatabase::database().transaction();
    QSqlQuery query;
    query.exec(sql);
    model->submitAll();
    model->database().commit();
    QMessageBox::information(this->confirm,"退票","退票成功",QMessageBox::Ok);
    this->confirm->hide();
}

void subwindow::nConfirmDelete()
{
    this->confirm->close();
}

QSqlTableModel *subwindow::getModel()
{
    return this->model;
}

passenger& subwindow::getNowPassenger()
{
    return this->nowPassenger;
}

void subwindow::on_startProvince_currentTextChanged(const QString &arg1)
{
    if(arg1=="北京"){
        QStringList beijingCity;
        beijingCity<<"北京";
        ui->startCity->clear();
        ui->startCity->addItems(beijingCity);
    }
    if(arg1=="河北"){
        QStringList hebeiCity;
        hebeiCity<<"石家庄"<<"保定"<<"秦皇岛";
        ui->startCity->clear();
        ui->startCity->addItems(hebeiCity);
    }
}

void subwindow::on_endProvince_currentTextChanged(const QString &arg1)
{
    if(arg1=="北京"){
        QStringList beijingCity;
        beijingCity<<"北京";
        ui->endCity->clear();
        ui->endCity->addItems(beijingCity);
    }
    if(arg1=="河北"){
        QStringList hebeiCity;
        hebeiCity<<"石家庄"<<"保定"<<"秦皇岛";
        ui->endCity->clear();
        ui->endCity->addItems(hebeiCity);
    }
}

void subwindow::on_purchaseButton_clicked(bool checked)
{
    if(ui->calendarWidget->selectedDate()<QDate::currentDate()){
        QMessageBox::warning(this,"错误","您购买的车票已过期",QMessageBox::Cancel);
    }else if(ui->startCity->currentText()==ui->endCity->currentText()){
        QMessageBox::warning(this,"错误","您选择的始发站和终点站相同",QMessageBox::Cancel);
    }else{
        for(int i=ui->numberSpinBox->text().toInt();i!=0;--i){
            QString id=this->nowPassenger.getId();
            QString name=this->nowPassenger.getName();
            QString startPro=ui->startProvince->currentText();
            QString startCity=ui->startCity->currentText();
            QString endPro=ui->endProvince->currentText();
            QString endCity=ui->endCity->currentText();
            QString seat=ui->seatComboBox->currentText();
            QString startTime=ui->calendarWidget->selectedDate().toString("yyyy-MM-dd");
            int price;
            switch(ui->seatComboBox->currentIndex()){
            case 0:
                price=150;
                break;
            case 1:
                price=300;
                break;
            case 2:
                price=50;
                break;
            case 3:
                price=500;
            }
            QString purchaseTime=QDate::currentDate().toString("yyyy-MM-dd");
            QDateTime current_date_time = QDateTime::currentDateTime();
            QString current_date = current_date_time.toString("ddhhmmsszzz");
            int row=model->rowCount();
            model->insertRow(row);
            model->setData(model->index(row,0),current_date);
            model->setData(model->index(row,1),id);
            model->setData(model->index(row,2),name);
            model->setData(model->index(row,3),startPro);
            model->setData(model->index(row,4),startCity);
            model->setData(model->index(row,5),endPro);
            model->setData(model->index(row,6),endCity);
            model->setData(model->index(row,7),seat);
            model->setData(model->index(row,8),startTime);
            model->setData(model->index(row,9),price);
            model->setData(model->index(row,10),purchaseTime);
            // 开始事务操作
            model->database().transaction();
            if (model->submitAll()) {
                model->database().commit(); //提交
                QMessageBox::information(this,"购票","购票成功",QMessageBox::Ok);
            } else {
                model->database().rollback(); //回滚
                qDebug() << "123456";
                QMessageBox::warning(this, tr("购票"),
                tr("数据库错误: %1").arg(model->lastError().text()));
            }
        }
    }
}

void subwindow::on_priceShowButton_clicked(bool checked)
{
    if(ui->calendarWidget->selectedDate()<QDate::currentDate()){
        QMessageBox::warning(this,"错误","您购买的车票已过期",QMessageBox::Cancel);
    }else if(ui->startCity->currentText()==ui->endCity->currentText()){
        QMessageBox::warning(this,"错误","您选择的始发站和终点站相同",QMessageBox::Cancel);
    }else{
        int amount=ui->numberSpinBox->text().toInt();
        int price;
        switch(ui->seatComboBox->currentIndex()){
        case 0:
            price=150*amount;
            break;
        case 1:
            price=300*amount;
            break;
        case 2:
            price=50*amount;
            break;
        case 3:
            price=500*amount;
            break;
        }
        ui->priceShowLable->setText(QString::number(price));
    }
}

void subwindow::on_refundButton_clicked(bool checked)
{
    this->confirm->show();
}

void subwindow::on_submitPushButton_clicked()
{
    if(ui->calendarWidget_2->selectedDate()<QDate::currentDate()){
        QMessageBox::warning(this,"错误","您购买的车票已过期",QMessageBox::Cancel);
    }else if(this->index.column()!=8){
        QMessageBox::warning(this,"错误","您只能修改始发时间",QMessageBox::Cancel);
    }else{
        QString startTime=ui->calendarWidget_2->selectedDate().toString("yyyy-MM-dd");
        this->model->setData(this->index,startTime);
        model->database().transaction();
        model->submitAll();
        model->database().commit(); //提交
        QMessageBox::information(this,"改签","改签成功",QMessageBox::Ok);
    }
}

void subwindow::on_CancelPushButton_clicked()
{
    model->database().rollback(); //回滚
    model->revertAll();
    QMessageBox::information(this,"改签","您已放弃改签",QMessageBox::Ok);
}

void subwindow::on_tableView_clicked(const QModelIndex &index)
{
    this->index=index;
}
