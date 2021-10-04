#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QFile file(":/res/map1.in");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    in >> mapsize_m >> mapsize_n;
    box_num=0;
    boom_num=0;
    for(int i=0; i<mapsize_m; i++)
    {
        for(int j=0; j<mapsize_n; j++)
        {
            in >> map1[i][j];
            map_boom[i][j] = map1[i][j];
            if(map1[i][j] == 3)
            {
                box_x[box_num] = 50+j*50;
                box_y[box_num++] = 50+i*50;
            }
            else if(map1[i][j] == 4)
            {
                person1_x = 50+j*50;
                person1_y = 50+i*50;
            }
            else if(map1[i][j] == 5)
            {
                hidden_point_x = 50+j*50;
                hidden_point_y = 50+i*50;
            }
            else if(map1[i][j] == 6)
            {
                goto_x = 50+j*50;
                goto_y = 50+i*50;
            }
        }
    }
    file.close();

    this->setStyleSheet("#MainWindow{border-image:url(:/res/background1.png);}");

    ui->step_count->setStyleSheet("font:25pt");
    ui->label->setStyleSheet("font:25pt");

    choose_person=false;

    connect(this, SIGNAL(Up_signal()), this, SLOT(Up()));
    connect(this, SIGNAL(Down_signal()), this, SLOT(Down()));
    connect(this, SIGNAL(Left_signal()), this, SLOT(Left()));
    connect(this, SIGNAL(Right_signal()), this, SLOT(Right()));
    connect(this, SIGNAL(check_wall_signal()), this, SLOT(check_wall()));
    connect(this, SIGNAL(check_pass_signal()), this, SLOT(check_pass()));
    connect(this, SIGNAL(boom_signal()), this, SLOT(boom()));
    connect(ui->restart_button, SIGNAL(clicked()), this, SLOT(restart()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Up() {
    person1_x_early = person1_x;
    person1_y_early = person1_y;
    person1_y = person1_y-50;

    step_num++;
    ui->label->setNum(step_num);

    for(int i=0; i<8; i++)
        if(person1_x == box_x[i] && person1_y == box_y[i])
        {
            box_x_early = box_x[i];
            box_y_early = box_y[i];
            box_y[i] = box_y[i]-50;
        }
}

void MainWindow::Down() {
    person1_x_early = person1_x;
    person1_y_early = person1_y;
    person1_y = person1_y+50;

    step_num++;
    ui->label->setNum(step_num);

    for(int i=0; i<8; i++)
        if(person1_x == box_x[i] && person1_y == box_y[i])
        {
            box_x_early = box_x[i];
            box_y_early = box_y[i];
            box_y[i] = box_y[i]+50;
        }
}

void MainWindow::Left() {
    person1_x_early = person1_x;
    person1_y_early = person1_y;
    person1_x = person1_x-50;

    step_num++;
    ui->label->setNum(step_num);

    for(int i=0; i<8; i++)
        if(person1_x == box_x[i] && person1_y == box_y[i])
        {
            box_x_early = box_x[i];
            box_y_early = box_y[i];
            box_x[i] = box_x[i]-50;
        }
}

void MainWindow::Right() {
    person1_x_early = person1_x;
    person1_y_early = person1_y;
    person1_x = person1_x+50;

    step_num++;
    ui->label->setNum(step_num);

    for(int i=0; i<8; i++)
    {
        if(person1_x == box_x[i] && person1_y == box_y[i])
        {
            box_x_early = box_x[i];
            box_y_early = box_y[i];
            box_x[i] = box_x[i]+50;
        }
    }
}

void MainWindow::restart() {
    box_num = 0;
    boom_num = 0;
    for(int i=0; i<mapsize_m; i++)
    {
        for(int j=0; j<mapsize_n; j++)
        {
            map1[i][j] = map_boom[i][j];
            if(map1[i][j] == 3)
            {
                box_x[box_num] = 50+j*50;
                box_y[box_num++] = 50+i*50;
            }
            else if(map1[i][j] == 4)
            {
                person1_x = 50+j*50;
                person1_y = 50+i*50;
            }
        }
    }

    if(now_level == 2)
    {
        label->setGeometry(200, 250, 0, 0);
        now_level--;
    }

    step_num = 0;
    ui->label->setNum(step_num);
}

void MainWindow::check_wall() {
    if(person1_x == hidden_point_x && person1_y == hidden_point_y)
    {
        person1_x = goto_x;
        person1_y = goto_y;
        for(int i=0; i<box_num; i++)
        {
            if(box_x[i] == goto_x&& box_y[i] == goto_y)
            {
                person1_x = hidden_point_x;
                person1_y = hidden_point_y;
            }
        }
    }

    for(int i=0; i<mapsize_m; i++)
    {
        for(int j=0; j<mapsize_n; j++)
        {
            if(map1[i][j] == 1 && person1_x == 50+j*50 && person1_y == 50+i*50)
            {
                person1_x = person1_x_early;
                person1_y = person1_y_early;
                step_num--;
                ui->label->setNum(step_num);
            }
            else
            {
                for(int k=0; k<8; k++)
                {
                    if(map1[i][j] == 1 && box_x[k] == 50+j*50 && box_y[k] == 50+i*50)
                    {
                        box_x[k] = box_x_early;
                        box_y[k] = box_y_early;
                        person1_x = person1_x_early;
                        person1_y = person1_y_early;
                        step_num--;
                        ui->label->setNum(step_num);
                    }
                    else
                    {
                        for(int l=0; l<8; l++)
                        {
                            if(l==k)
                                continue;
                            else if(box_x[l] == box_x[k] && box_y[l] == box_y[k])
                            {
                                box_x[k] = box_x_early;
                                box_y[k] = box_y_early;
                                person1_x = person1_x_early;
                                person1_y = person1_y_early;
                                step_num--;
                                ui->label->setNum(step_num);
                            }
                        }
                    }
                }
            }
        }
    }
}

void MainWindow::check_pass() {
    int box_on_dot=0;
    for(int i=0; i<mapsize_m; i++)
    {
        for(int j=0; j<mapsize_n; j++)
        {
            for(int k=0; k<box_num; k++)
            {
                if(map1[i][j] == 2 && box_x[k] == 50+j*50 && box_y[k] == 50+i*50)
                {
                    box_on_dot++;
                    if(box_on_dot == box_num)
                    {
                        if(now_level++ == 1)
                        {
                            label->setGeometry(200, 200, 350, 350);

                            label->setMovie(movie);
                            label->setScaledContents(true);
                            movie->start();

                            break;
                        }
                        next_level();
                    }
                    break;
                }
            }
        }
    }
}

void MainWindow::next_level() {
    this->setStyleSheet("#MainWindow{border-image:url(:/res/background3.png);}");

    for(int i=0; i<8; i++)
    {
        box_x[i]=0;
        box_y[i]=0;
    }

    QFile file(":/res/map.in");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    in >> mapsize_m >> mapsize_n;
    box_num=0;
    boom_num=0;
    for(int i=0; i<mapsize_m; i++)
    {
        for(int j=0; j<mapsize_n; j++)
        {
            in >> map1[i][j];
            map_boom[i][j] = map1[i][j];
            if(map1[i][j] == 3)
            {
                box_x[box_num] = 50+j*50;
                box_y[box_num++] = 50+i*50;
            }
            else if(map1[i][j] == 4)
            {
                person1_x = 50+j*50;
                person1_y = 50+i*50;
            }
            else if(map1[i][j] == 5)
            {
                hidden_point_x = 50+j*50;
                hidden_point_y = 50+i*50;
            }
            else if(map1[i][j] == 6)
            {
                goto_x = 50+j*50;
                goto_y = 50+i*50;
            }
        }
    }
    file.close();

    step_num = 0;
    ui->label->setNum(step_num);
}

void MainWindow::boom() {
    if(boom_num == 1)
        return;
    boom_num++;

    for(int i=-1; i<2; i++)
    {
        for(int j=-1; j<2; j++)
        {
            if((person1_y-50)/50 +i != 0 && (person1_y-50)/50 +i != 7 &&
               (person1_x-50)/50 +j != 0 && (person1_x-50)/50 +j != 7 &&
               map1[(person1_y-50)/50 +i][(person1_x-50)/50 +j] == 1)
            {
                map1[(person1_y-50)/50 +i][(person1_x-50)/50 +j] = 0;
            }
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
    if(e->key() == Qt::Key_Up && now_level != 2 && choose_person == true) {
        emit Up_signal();
        emit check_wall_signal();
        emit check_pass_signal();
    }
    if(e->key() == Qt::Key_Down && now_level != 2 && choose_person == true) {
        emit Down_signal();
        emit check_wall_signal();
        emit check_pass_signal();
    }
    if(e->key() == Qt::Key_Left && now_level != 2 && choose_person == true) {
        emit Left_signal();
        emit check_wall_signal();
        emit check_pass_signal();
    }
    if(e->key() == Qt::Key_Right && now_level != 2 && choose_person == true) {
        emit Right_signal();
        emit check_wall_signal();
        emit check_pass_signal();
    }
    if(e->key() == Qt::Key_Q && choose_person == true) {
        emit boom_signal();
    }
    if(e->key() == Qt::Key_1 && choose_person==false) {
        choose_person = true;
        num_person=1;
    }
    if(e->key() == Qt::Key_2 && choose_person==false) {
        choose_person = true;
        num_person=2;
    }
    if(e->key() == Qt::Key_3 && choose_person==false) {
        choose_person = true;
        num_person=3;
    }
}

void MainWindow::paintEvent(QPaintEvent*) {
    QPainter map(this);

    QPixmap wall(":/res/wall.png");
    QPixmap dot(":/res/dot.png");
    QPixmap box(":/res/box2.png");
    QPixmap pass(":/res/pass.gif");

    for(int i=0; i<mapsize_m; i++)
    {
        for(int j=0; j<mapsize_n; j++)
        {
            if(map1[i][j] == 1)
                map.drawPixmap(50+j*50, 50+i*50, 50, 50, wall);
            else if(map1[i][j] == 2)
                map.drawPixmap(50+j*50, 50+i*50, 50, 50, dot);
        }
    }

    if(num_person == 1)
    {
        QPixmap person(":/res/person1.png");
        map.drawPixmap(person1_x, person1_y, 50, 50, person);
    }
    else if(num_person == 2)
    {
        QPixmap person(":/res/person2.png");
        map.drawPixmap(person1_x, person1_y, 50, 50, person);
    }
    else if(num_person == 3)
    {
        QPixmap person(":/res/person3.png");
        map.drawPixmap(person1_x, person1_y, 50, 50, person);
    }
    else
    {
        QPixmap person;
        map.drawPixmap(person1_x, person1_y, 50, 50, person);
    }

    for(int i=0; i<box_num; i++)
        map.drawPixmap(box_x[i], box_y[i], 50, 50, box);

    update();
}
