#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(0, 0, 1201, 871)),
    timer_sword(new QTimer),
    timer_doodle_jump(new QTimer),
    have_choose(0),
    click_puase(0),
    score_num(0),
    re(0),
    change_restart(0)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);

    background = new map_p;
    background->setPixmap(QPixmap(":/res/background.png").scaled(400, 610));
    background->setPos(400,130);
    scene->addItem(static_cast<QGraphicsPixmapItem*>(background));

    connect(ui->pauseButton, SIGNAL(clicked()), this, SLOT(pause()));

    srand( static_cast<unsigned int>(time(nullptr)));
    platform_x = static_cast<int>(static_cast<double>(rand()) /
                                  (RAND_MAX + 1.0) * (735.0 - 390.0) +390.0);
    platform_y = 718;

    doodle_o = new doodle;      //set origin doodle
    doodle_o->setPos(platform_x-2.5,platform_y);
    doodle_o->connect(timer_doodle_jump, SIGNAL(timeout()), doodle_o, SLOT(jump()));
    scene->addItem(static_cast<QGraphicsPixmapItem*>(doodle_o));
    scene->addItem(static_cast<QGraphicsPixmapItem*>(doodle_o->game_over));
    timer_doodle_jump->start(7);

    ui->final_score->setStyleSheet("QLabel {font:20pt; color:yellow; }");
    ui->final_score->setGeometry(500,0,300,300);
    ui->score->setStyleSheet("QLabel {font:15pt; color:white; }");
    connect(doodle_o, SIGNAL(add_score_signal()), this, SLOT(add_score()));
    connect(doodle_o, SIGNAL(changeDoodle_signal()), this, SLOT(changeDoodle()));

    paint_origin_map();
    paint_origin_hazard();

    timer_sword->start(5);

    QMediaPlayer *music = new QMediaPlayer();       //background music
    music->setMedia(QUrl("qrc:/res/background_music.mp3"));
    music->play();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pause() {
    if(click_puase==0)
    {
        doodle_o->pause_sig=1;
        click_puase=1;
        ui->pauseButton->setIcon(QIcon(":/res/start.png"));
    }
    else if (click_puase==1)
    {
        doodle_o->pause_sig=0;
        click_puase=0;
        ui->pauseButton->setIcon(QIcon(":/res/pause.png"));
    }
    else if(click_puase==2) //for restart
    {
        restart();
        click_puase=0;
        ui->pauseButton->setIcon(QIcon(":/res/pause.png"));
    }
}

void MainWindow::restart() {
    change_restart=1;

    score_num=0;    //reset score
    ui->score->setStyleSheet("QLabel {font:15pt; color:white; }");
    ui->score->setGeometry(10,-10,51,61);
    ui->score->setNum(0);
    ui->final_score->setGeometry(1000,0,300,300);

    doodle_o->game_over->setPos(1000,0);    //reset doodle--------------------
    doodle_o->gameover_add_score=0;
    doodle_o->pause_sig=0;
    doodle_o->have_protect=0;

    if(doodle_o->change_doodle==4){
    }
    else
        doodle_o->change_doodle=0;

    platform_x = static_cast<int>(static_cast<double>(rand()) /
                                  (RAND_MAX + 1.0) * (735.0 - 390.0) +390.0);
    platform_y = 718;
    paint_origin_map();                     //reset map

    if(doodle_o->which_doodle==1)
        doodle_o->setPixmap(QPixmap(":/res/doodle.png").scaled(60, 60));
    else if(doodle_o->which_doodle==2)
        doodle_o->setPixmap(QPixmap(":/res/doodle 2.png").scaled(60, 60));
    else if(doodle_o->which_doodle==3)
        doodle_o->setPixmap(QPixmap(":/res/doodle 3.png").scaled(60, 60));
    doodle_o->setPos(doodle_o->check_platform.at(0)->x(), 650);
                                            //reset doodle---------------------
    paint_origin_hazard();      //reset hazard

    re=0;
}

void MainWindow::paint_origin_map() {
    if(re==0)
    {
        for(int i=0; i<20; i++)
        {
            map_p *p;
            if(i!=0)
            {
                platform_x = static_cast<int>(static_cast<double>(rand()) /
                                              (RAND_MAX + 1.0) * (735.0 - 390.0) +390.0);
                platform_y = platform_y - static_cast<int>(static_cast<double>(rand()) /
                                                         (RAND_MAX + 1.0) * (53.0 -47.0) +47.0);
            }
            if(i==14)                       //for move platform
            {
                p = new platform2;
                p->setPixmap(QPixmap(":/res/platform_moving.png").scaled(55, 12));
                p->platform_type=2;
            }
            else if(i==5 || i==11 || i==17)//for transparent platform
            {
                p = new platform1;
                p->setPixmap(QPixmap(":/res/platform_transparent.png").scaled(55, 12));
                p->platform_type=1;
            }
            else                            //for normal platform
            {
                p = new platform0;
                p->setPixmap(QPixmap(":/res/platform_normal.png").scaled(55, 12));
                p->platform_type=0;
            }

            if(i==10)                       //for spring
            {
                p->have_spring=1;
                doodle_o->spring->setPixmap(QPixmap(":/res/spring_press.png").scaled(20, 20));
                doodle_o->spring->setPos(platform_x+12, platform_y-20);
                doodle_o->spring->connect(timer_doodle_jump, SIGNAL(timeout()), doodle_o->spring, SLOT(roll()));
                scene->addItem(static_cast<QGraphicsPixmapItem*>(doodle_o->spring));
            }
            if(i==15)                       //for shield
            {
                p->have_shield=1;
                doodle_o->protection_shield->setPixmap(QPixmap(":/res/protection_shield.png").scaled(20, 23));
                doodle_o->protection_shield->setPos(platform_x+40, platform_y-23);
                doodle_o->protection_shield->connect(timer_doodle_jump, SIGNAL(timeout()), doodle_o->protection_shield, SLOT(roll()));
                scene->addItem(static_cast<QGraphicsPixmapItem*>(doodle_o->protection_shield));
            }
            if(i==18)                       //for rocket
            {
                p->have_rocket=1;
                doodle_o->rocket->setPixmap(QPixmap(":/res/rocket.png").scaled(25, 30));
                doodle_o->rocket->setPos(platform_x+30, platform_y-30);
                doodle_o->rocket->connect(timer_doodle_jump, SIGNAL(timeout()), doodle_o->rocket, SLOT(roll()));
                scene->addItem(static_cast<QGraphicsPixmapItem*>(doodle_o->rocket));
            }

            p->setPos(platform_x,platform_y);
            p->connect(timer_doodle_jump, SIGNAL(timeout()), p, SLOT(roll()));
            scene->addItem(static_cast<QGraphicsPixmapItem*>(p));

            doodle_o->check_platform.push_back(p);
        }
    }
    else if(re==1)
    {
        if(doodle_o->check_platform.at(0)->platform_type == 1 ||
           doodle_o->check_platform.at(0)->platform_type == 2)
            swap(doodle_o->check_platform.at(0),doodle_o->check_platform.at(1));

        for(unsigned int i=0; i<20; i++)
        {
            if(i!=0)
            {
                platform_x = static_cast<int>(static_cast<double>(rand()) /
                                              (RAND_MAX + 1.0) * (735.0 - 390.0) +390.0);
                platform_y = platform_y - static_cast<int>(static_cast<double>(rand()) /
                                                         (RAND_MAX + 1.0) * (53.0 -47.0) +47.0);
            }
            doodle_o->check_platform.at(i)->setPos(platform_x, platform_y);

            if(doodle_o->check_platform.at(i)->have_spring)
                doodle_o->spring->setPos(platform_x+12, platform_y-20);
            if(doodle_o->check_platform.at(i)->have_shield)
                doodle_o->protection_shield->setPos(platform_x+40, platform_y-23);
            if(doodle_o->check_platform.at(i)->have_rocket)
                doodle_o->rocket->setPos(platform_x+30, platform_y-30);
        }
    }
}

void MainWindow::paint_origin_hazard() {
    if(re==0)
    {
        platform_x = static_cast<int>(static_cast<double>(rand()) /
                                      (RAND_MAX + 1.0) * (735.0 - 390.0) +390.0);
        platform_y = static_cast<int>(static_cast<double>(rand()) /
                                                 (RAND_MAX + 1.0) * (-1000.0 +1200.0) -1200.0);

        doodle_o->monster->setPixmap(QPixmap(":/res/monster.png").scaled(44, 70));
        doodle_o->monster->setPos(platform_x, platform_y);
        doodle_o->monster->connect(timer_doodle_jump, SIGNAL(timeout()), doodle_o->monster, SLOT(roll()));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(doodle_o->monster));
        //monster---------
        platform_x = static_cast<int>(static_cast<double>(rand()) /
                                      (RAND_MAX + 1.0) * (735.0 - 390.0) +390.0);
        platform_y = static_cast<int>(static_cast<double>(rand()) /
                                                 (RAND_MAX + 1.0) * (-2000.0 +2500.0) -2500.0);

        doodle_o->blackhole->setPixmap(QPixmap(":/res/blackhole.png").scaled(80, 80));
        doodle_o->blackhole->setPos(platform_x, platform_y);
        doodle_o->blackhole->connect(timer_doodle_jump, SIGNAL(timeout()), doodle_o->blackhole, SLOT(roll()));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(doodle_o->blackhole));
        //blackhole-------
    }
    else if(re==1)
    {
        platform_x = static_cast<int>(static_cast<double>(rand()) /
                                      (RAND_MAX + 1.0) * (735.0 - 390.0) +390.0);
        platform_y = static_cast<int>(static_cast<double>(rand()) /
                                                 (RAND_MAX + 1.0) * (-1000.0 +1200.0) -1200.0);
        doodle_o->monster->setPos(platform_x, platform_y);

        platform_x = static_cast<int>(static_cast<double>(rand()) /
                                      (RAND_MAX + 1.0) * (735.0 - 390.0) +390.0);
        platform_y = static_cast<int>(static_cast<double>(rand()) /
                                                 (RAND_MAX + 1.0) * (-2000.0 +2500.0) -2500.0);
        doodle_o->blackhole->setPos(platform_x, platform_y);
    }
}

void MainWindow::add_score() {
    if(doodle_o->gameover_add_score==0)
    {
        score_num++;
        ui->score->setNum(score_num*23);
    }
}

void MainWindow::changeDoodle() {
    if(doodle_o->change_doodle == 0)        //to rocket
    {
        if(change_restart==0)
            doodle_o->setPixmap(QPixmap(":/res/rocket_fire.png").scaled(45, 60));
        else
            change_restart=0;
    }
    else if(doodle_o->change_doodle == 1)   //to origin
    {
        if(doodle_o->which_doodle==1)
            doodle_o->setPixmap(QPixmap(":/res/doodle.png").scaled(60, 60));
        else if(doodle_o->which_doodle==2)
            doodle_o->setPixmap(QPixmap(":/res/doodle 2.png").scaled(60, 60));
        else if(doodle_o->which_doodle==3)
            doodle_o->setPixmap(QPixmap(":/res/doodle 3.png").scaled(60, 60));
        doodle_o->have_protect=0;
    }
    else if(doodle_o->change_doodle == 2)   //to shield
    {
        if(doodle_o->which_doodle==1)
            doodle_o->setPixmap(QPixmap(":/res/doodle_shield.png").scaled(60, 60));
        else if(doodle_o->which_doodle==2)
            doodle_o->setPixmap(QPixmap(":/res/doodle 2_shield.png").scaled(60, 60));
        else if(doodle_o->which_doodle==3)
            doodle_o->setPixmap(QPixmap(":/res/doodle 3_shield.png").scaled(60, 60));
        doodle_o->change_doodle=4;
        QTimer::singleShot(5 * 1000, this, SLOT(changeDoodle()));
    }
    else if(doodle_o->change_doodle == 3)   //to gameover
    {
        doodle_o->setPos(0,1000);
        ui->final_score->setGeometry(50,240,300,300);
        ui->score->setStyleSheet("QLabel {font:20pt; color:yellow; }");
        ui->score->setGeometry(200,240,300,300);
        ui->pauseButton->setIcon(QIcon(":/res/restart.png"));
        click_puase=2;
        re=1;
    }
    else if(doodle_o->change_doodle == 4)   //shield tp origin
    {
        if(doodle_o->which_doodle==1)
            doodle_o->setPixmap(QPixmap(":/res/doodle.png").scaled(60, 60));
        else if(doodle_o->which_doodle==2)
            doodle_o->setPixmap(QPixmap(":/res/doodle 2.png").scaled(60, 60));
        else if(doodle_o->which_doodle==3)
            doodle_o->setPixmap(QPixmap(":/res/doodle 3.png").scaled(60, 60));
        doodle_o->have_protect=0;
    }
}


void MainWindow::keyPressEvent(QKeyEvent *e) {
    if(e->key() == Qt::Key_1 && have_choose!=1) {       //choose doodle-----------
        doodle_o->which_doodle=1;
        have_choose=1;
        doodle_o->setPixmap(QPixmap(":/res/doodle.png").scaled(60, 60));
    }
    else if(e->key() == Qt::Key_2 && have_choose!=1) {
        doodle_o->which_doodle=2;
        have_choose=1;
        doodle_o->setPixmap(QPixmap(":/res/doodle 2.png").scaled(60, 60));
    }
    else if(e->key() == Qt::Key_3 && have_choose!=1) {
        doodle_o->which_doodle=3;
        have_choose=1;
        doodle_o->setPixmap(QPixmap(":/res/doodle 3.png").scaled(60, 60));
    }                                                   //choose doodle-----------
    else if(e->key() == Qt::Key_Left && doodle_o->pause_sig==0) {
        doodle_o->setPos(doodle_o->x() - 10, doodle_o->y());
        if(doodle_o->x() <= 370.0)
            doodle_o->setPos(770, doodle_o->y());
    }
    else if(e->key() == Qt::Key_Right && doodle_o->pause_sig==0) {
        doodle_o->setPos(doodle_o->x() + 10, doodle_o->y());
        if(doodle_o->x() >= 770.0)
            doodle_o->setPos(370, doodle_o->y());
    }
    if(e->key() == Qt::Key_Space && doodle_o->pause_sig==0 && doodle_o->change_doodle!=2 &&
            doodle_o->rocket->now_rocket!=1) {
        sword *b = new sword;

        b->setPixmap(QPixmap(":/res/sword.png").scaled(20, 70));
        b->setPos(doodle_o->x() + doodle_o->pixmap().width() / 2 - b->pixmap().width() / 2, doodle_o->y() - b->pixmap().height());
        b->connect(timer_sword, SIGNAL(timeout()), b, SLOT(fly()));
        b->connect(timer_sword, SIGNAL(timeout()), this, SLOT(check_sword_hit_monster()));
        scene->addItem(static_cast<QGraphicsPixmapItem*>(b));

        s.push_back(b);
    }
}

void MainWindow::check_sword_hit_monster() {
    sword *temp;
    for(unsigned int i=0; i<s.size(); i++)
    {
        if( (s.at(i)->x() <= doodle_o->monster->x()+42 && s.at(i)->x()+20 >= doodle_o->monster->x() )
          &&(s.at(i)->y() <= doodle_o->monster->y()+70 && s.at(i)->y() >= doodle_o->monster->y())   )
        {
            doodle_o->monster->setPos(1000,doodle_o->monster->y());
            temp=s.at(i);
            s.erase(s.begin()+i);
            scene->removeItem(temp);
            delete temp;
            break;
        }
        if(s.at(i)->y() < 0) {
            temp=s.at(i);
            s.erase(s.begin()+i);
            scene->removeItem(temp);
            delete temp;
        }
    }
}
