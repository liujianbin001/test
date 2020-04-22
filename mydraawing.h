#ifndef MYDRAAWING_H
#define MYDRAAWING_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QTableView>
#include <QMessageBox>
#include <QSqlError>

class mydraawing : public QWidget
{
    Q_OBJECT
public:
    explicit mydraawing(QWidget *parent = nullptr);


private:
    int clume_num;
    int row_num;
    int pic_num;
    void func_zoom(double &pos_y, double angle);
    void func_rotate(double &pos_x , double &pos_y, double angle);
    void translation_axis(int &pos_x,int & pos_y);
    double anglefunc_m2E(double angle_M,double vec_e);



signals:


public:
    QSqlTableModel *model;

   int setNum(int num);
protected:
    void paintEvent(QPaintEvent *event);


public slots:
};

#endif // MYDRAAWING_H
