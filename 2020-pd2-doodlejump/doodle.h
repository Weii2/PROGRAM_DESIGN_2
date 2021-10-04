#ifndef DOODLE_H
#define DOODLE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

#include "map_p.h"

#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;

class doodle : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    doodle();
    vector<map_p*> check_platform;
    map_p *spring;
    map_p *rocket;
    map_p *monster;
    map_p *blackhole;
    map_p *protection_shield;
    map_p *game_over;
    int gameover_add_score;
    int pause_sig;
    int change_doodle;
    int have_protect;
    int which_doodle;

public slots:
    void jump();

signals:
    void add_score_signal();
    void changeDoodle_signal();

private:
    int num_up;
    int num_down;
    int num_transparent_platform;
    int doodle_on_platform;
    double dis;
};


#endif // DOODLE_H
