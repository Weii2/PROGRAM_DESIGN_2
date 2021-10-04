#ifndef MAP_P_H
#define MAP_P_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class map_p : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    map_p();
    double distance;
    int platform_type;
    int set0;
    int have_spring;
    int have_rocket;
    int have_shield;
    int now_rocket;

public slots:
    virtual void roll();
};

class platform0 : public map_p
{
    Q_OBJECT
};

class platform1 : public map_p
{
    Q_OBJECT
};

class platform2 : public map_p
{
    Q_OBJECT
public:
    platform2();

public slots:
    virtual void roll();

private:
    int move_to_right;
};

#endif // MAP_P_H
