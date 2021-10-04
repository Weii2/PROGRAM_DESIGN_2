#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QObject>

#include "sword.h"
#include "doodle.h"

#include <QKeyEvent>

#include <QMediaPlayer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void choose_doodle();
    void paint_origin_map();
    void paint_origin_hazard();
    void restart();

public slots:
    virtual void keyPressEvent(QKeyEvent *e);
    void add_score();
    void pause();
    void changeDoodle();
    void check_sword_hit_monster();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    doodle *doodle_o;
    map_p *background;
    vector<sword*> s;
    QTimer *timer_sword;
    QTimer *timer_doodle_jump;

    int have_choose;
    int click_puase;
    int score_num;
    int platform_x, platform_y;
    int re;
    int change_restart;
};

#endif // MAINWINDOW_H
