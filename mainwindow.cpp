#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include <star.h>
#include <QDebug>





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    star *firststar =new star;
    firststar->star_init();

    model = new QSqlTableModel(this);
    model->setTable("SunMoon");
    // 设置编辑策略
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    ui->sun_moon->setModel(model);

    model_sat = new QSqlTableModel(this);
    model_sat->setTable("satllite");
    model_sat->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_sat->select();
    ui->satllite->setModel(model_sat);



    ui->widget_1->setNum(1);
    ui->widget_2->setNum(2);
    ui->widget->setNum(3);




    // 创建 pixmap

//    pixmap = QPixmap(100, 100);

//    pixmap.fill(Qt::gray);

//    QPainter painter(&pixmap);

//    painter.drawRect(10, 10, 80, 80);

//    painter.drawText(20, 30, "Hello World");



//    // 使用 pixmap

//    ui->label->setPixmap(pixmap);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_search_clicked()
{
    QString name = ui->lineEdit_search->text();

    // 根据姓名进行筛选，一定要使用单引号
    model->setFilter(QString("name = '%1'").arg(name));
    model->select();
}

void MainWindow::on_pushButton_showall_clicked()
{
    model->setTable("SunMoon");
    model->select();
}

void MainWindow::on_pushButton_add_clicked()
{
    // 获得表的行数
    int rowNum = model->rowCount();
    int id = 10;

    // 添加一行
    model->insertRow(rowNum);
    model->setData(model->index(rowNum, 0), id);

    // 可以直接提交
    //model->submitAll();
}

void MainWindow::on_pushButton_delete_clicked()
{
    // 获取选中的行
    int curRow = ui->sun_moon->currentIndex().row();

    // 删除该行
    model->removeRow(curRow);
    int ok = QMessageBox::warning(this,tr("删除当前行!"),
                                  tr("你确定删除当前行吗？"), QMessageBox::Yes, QMessageBox::No);
    if(ok == QMessageBox::No)
    { // 如果不删除，则撤销
        model->revertAll();
    } else { // 否则提交，在数据库中删除该行
        model->submitAll();
    }
}

void MainWindow::on_pushButton_update_clicked()
{
    // 开始事务操作
    model->database().transaction();
    if (model->submitAll()) {
        if(model->database().commit()) // 提交
            QMessageBox::information(this, tr("tableModel"),
                                     tr("数据修改成功！"));
    } else {
        model->database().rollback(); // 回滚
        QMessageBox::warning(this, tr("tableModel"),
                             tr("数据库错误: %1").arg(model->lastError().text()),
                             QMessageBox::Ok);
    }
}

void MainWindow::on_bserch_sta_clicked()
{
    QString name = ui->serch_sat->text();

    // 根据姓名进行筛选，一定要使用单引号
    model_sat->setFilter(QString("name = '%1'").arg(name));
    model_sat->select();
}

void MainWindow::on_all_sta_clicked()
{
    model_sat->setTable("satllite");
    model_sat->select();
}

void MainWindow::on_add_sta_clicked()
{
    // 获得表的行数
    int rowNum = model_sat->rowCount();
    int id = 10;

    // 添加一行
    model_sat->insertRow(rowNum);
    model_sat->setData(model_sat->index(rowNum, 0), id);

    // 可以直接提交
    //model->submitAll();
}

void MainWindow::on_delete_sta_clicked()
{
    // 获取选中的行
    int curRow = ui->satllite->currentIndex().row();

    // 删除该行
    model_sat->removeRow(curRow);
    int ok = QMessageBox::warning(this,tr("删除当前行!"),
                                  tr("你确定删除当前行吗？"), QMessageBox::Yes, QMessageBox::No);
    if(ok == QMessageBox::No)
    { // 如果不删除，则撤销
        model_sat->revertAll();
    }
    else
    { // 否则提交，在数据库中删除该行
        model_sat->submitAll();
    }
}

void MainWindow::on_update_sta_clicked()
{
    // 开始事务操作
    model_sat->database().transaction();
    if (model_sat->submitAll())
    {
        if(model_sat->database().commit()) // 提交
            QMessageBox::information(this, tr("tableModel"),
                                     tr("数据修改成功！"));
    }
    else
    {
        model_sat->database().rollback(); // 回滚
        QMessageBox::warning(this, tr("tableModel"),
                             tr("数据库错误: %1").arg(model_sat->lastError().text()),
                             QMessageBox::Ok);
    }
}
