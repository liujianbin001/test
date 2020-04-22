#include "star.h"
#include <QtMath>

star::star(QObject *parent) : QObject(parent)
{

}

void star::star_init()
{
    //change to rand later
    position_x=0;
    position_y=1;
    spead=1;
    spead_angle=0;
    star_weight=1;


}

void star::func_move(double fra)
{

    double accelery;
    double accelery_angle;
    double sp_x;
    double sp_y;
    double acc_x;
    double acc_y;
    //计算加速度 F=G*M*m/r/r  a=G*M/r/r   m=1000;G=10
    sp_y=spead*qSin(spead_angle);
    sp_x=spead*qCos(spead_angle);
    accelery=10000/(qPow(position_x,2)*qPow(position_y,2));
    accelery_angle=qAtan2(-position_y,-position_x);
    acc_y=accelery*qSin(accelery_angle);
    acc_x=accelery*qCos(accelery_angle);
    spead_angle=qAtan2(sp_y+acc_y*fra,sp_x+acc_x*fra);
    position_x=position_x+sp_x*fra;
    position_y=position_y+sp_y*fra;
}
