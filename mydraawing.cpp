#include "mydraawing.h"

#include "connection.h"
#include <QPainter>
#include <QDebug>
#include <QtMath>

mydraawing::mydraawing(QWidget *parent) : QWidget(parent)
{
    pic_num=0;
    if (!createConnection())
        qDebug()<<"mei lianjieshang";
    else
        qDebug()<<"lianjieshang";

    model = new QSqlTableModel(this);

    model->setTable("satllite");
    //model->setEditStrategy(QSqlTableModel::OnManualSubmit);


    // 设置编辑策略
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    row_num=model->rowCount();








}

void mydraawing::func_zoom(double &pos_y, double angle)
{
    pos_y=pos_y*qCos(angle);
}

void mydraawing::func_rotate(double &pos_x, double &pos_y, double angle)
{
    double angle_1;
    double radius;
    angle_1=qAtan2(pos_y,pos_x);
    radius=qPow(qPow(pos_x,2)+qPow(pos_y,2),0.5);
    pos_x=radius*qCos(angle_1+angle);
    pos_y=radius*qSin(angle_1+angle);
}

void mydraawing::translation_axis(int &pos_x, int &pos_y)
{
    pos_x=pos_x+600;
    pos_y=400-pos_y;
}

double mydraawing::anglefunc_m2E(double angle_M, double vec_e)
{
    double angle_E;
    double delta;
    delta=qAtan2(0,-1);
    angle_E=qAtan2(0,-1);
    //qDebug()<<delta<<angle_E<<angle_M<<qPow(10,-5);
    while(qAbs(delta) >qPow(10,-5))
    {
        qDebug()<<delta<<angle_E<<angle_M;
        delta=angle_E-vec_e*qSin(angle_E)-angle_M;
        if(delta>0)
            angle_E+=-delta/2;
        else
            angle_E-=delta/2;
    }
    return angle_E;
}

int mydraawing::setNum(int num)
{
    pic_num=num;
    return  num;
}

void mydraawing::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    double r;
    double aaa;
    double bbb;
    double ccc;
    double eee;
    double the_i;
    double the_om;
    double the_w;
    double the_mo; //平近点角
    double the_mo1;//偏近点角
    double the_mo2;//真近点角
    double the;
    QString name_star;
    int x0,y0;
    int xxx,yyy;
    double xx;
    double yy;


    //painter.drawLine(QPoint(0, 0), QPoint(100, 100));

    //创建画笔
    QPen pen(Qt::darkRed, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    //使用画笔
    painter.setPen(pen);

    x0=0;
    y0=0;
    xxx=100;
    yyy=0;
    translation_axis(x0,y0);
    translation_axis(xxx,yyy);
    painter.drawLine(QPoint(x0, y0), QPoint(xxx, yyy));
    xxx=0;
    yyy=100;
    translation_axis(xxx,yyy);
    painter.drawLine(QPoint(x0, y0), QPoint(xxx, yyy));



    for(int j=0;j<row_num;j++)
    {
        name_star=model->record(j).value(1).toString();//名称
        aaa=model->record(j).value(2).toDouble(); //长半轴
        eee=model->record(j).value(3).toDouble(); //偏心率
        ccc=aaa*eee;                              //焦距
        bbb=qPow(aaa*aaa-ccc*ccc,0.5);
        the_i=model->record(j).value(4).toDouble()*(qAtan2(0,-1)/180);  //轨道倾角i        
        the_om=model->record(j).value(5).toDouble()*(qAtan2(0,-1)/180); //升交点黄经om
        the_w=model->record(j).value(6).toDouble()*(qAtan2(0,-1)/180);  //近日点辐角w
        the_mo=model->record(j).value(7).toDouble()*(qAtan2(0,-1)/180); //平近点角

        //the_mo1=qAtan(qTan(the_mo-the_om)/qCos(the_i))*180/qAtan2(0,-1);
        the_mo1=anglefunc_m2E(the_mo,eee);
        xx=aaa*qCos(the_mo1)-ccc;             //偏近点角
        yy=aaa*qSin(the_mo1)*bbb/aaa;
        the_mo2=qAtan2(yy,xx);
        if(the_mo2<0)
            the_mo2+=2*qAtan2(0,-1);
        qDebug()<<the_mo<<the_mo1<<the_mo2;


        //the_mo1=(the_mo1+360)/180;


        for(int i=0;i<630;i++)
        {
            the=i;
            the=the/100;
            //椭圆极坐标公式+近日点偏角mo
            r=bbb*bbb/(aaa-ccc*qCos(the-the_w-qAtan2(0,-1)));
            //计算xy值
            xx=r*qCos(the);
            yy=r*qSin(the);
            //根据轨道倾角i 对x轴进行缩放
            func_zoom(yy,the_i);
            //根据升交点黄经 金星旋转
            func_rotate(xx,yy,the_om);
//            xxx=QString::number(xx/qPow(10,10.4),'f',0).toInt();
//            yyy=QString::number(yy/qPow(10,10.4),'f',0).toInt();

            switch (pic_num)
            {
                case 0: break;
            case 1:
                xxx=QString::number(xx/qPow(10,5),'f',0).toInt();
                yyy=QString::number(yy/qPow(10,5),'f',0).toInt();
                break;
            case 2:
                xxx=QString::number(xx/qPow(10,4),'f',0).toInt();
                yyy=QString::number(yy/qPow(10,4),'f',0).toInt();
                break;
            case 3:
                xxx=QString::number(xx/qPow(10,5),'f',0).toInt();
                yyy=QString::number(yy/qPow(10,5),'f',0).toInt();
                break;
            default: break;
            }

            translation_axis(xxx,yyy);
            painter.drawPoint(xxx,yyy);
            xx=6400000*qCos(the);
            yy=6400000*qSin(the);

            xxx=QString::number(xx/qPow(10,5),'f',0).toInt();
            yyy=QString::number(yy/qPow(10,5),'f',0).toInt();

            translation_axis(xxx,yyy);
            painter.drawPoint(xxx,yyy);

        }

    }

}
