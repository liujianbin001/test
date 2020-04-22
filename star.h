#ifndef STAR_H
#define STAR_H

#include <QObject>

class star : public QObject
{
    Q_OBJECT
public:
    explicit star(QObject *parent = nullptr);




private:


   double spead;
   double spead_angle;
   double star_id;
   double star_weight;
   double frame;

public:
   void star_init();
   void func_move(double fra);
   double position_x;
   double position_y;


signals:

public slots:
};

#endif // STAR_H
