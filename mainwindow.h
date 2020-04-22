#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QTableView>
#include <QMessageBox>
#include <QSqlError>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_search_clicked();

    void on_pushButton_showall_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_update_clicked();

    void on_bserch_sta_clicked();

    void on_all_sta_clicked();

    void on_add_sta_clicked();

    void on_delete_sta_clicked();

    void on_update_sta_clicked();

private:
    Ui::MainWindow *ui;

    QSqlTableModel *model;
    QSqlTableModel *model_sat;

};
#endif // MAINWINDOW_H
