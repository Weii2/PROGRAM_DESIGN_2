#include "doodle.h"

doodle::doodle() :
    gameover_add_score(0),
    pause_sig(0),
    change_doodle(0),
    have_protect(0),
    which_doodle(0),
    num_up(0),
    num_down(0),
    num_transparent_platform(0),
    doodle_on_platform(0),
    dis(100)
{
    srand( static_cast<unsigned int>(time(nullptr)));

    spring = new map_p;
    rocket = new map_p;
    monster = new map_p;
    blackhole = new map_p;
    protection_shield = new map_p;
    game_over = new map_p;
}

void doodle::jump()
{
    if(pause_sig==1)
        return;

    if(which_doodle==0)
        return;

    if(num_up<100) {                //jump up
        if(dis>60 && rocket->now_rocket==0)
            setPos(x(), y() - (200-dis)/(dis/2));
        else if(rocket->now_rocket==1)
            setPos(x(), y() - 0.75);
        else
            setPos(x(), y() - 2);
        num_up++;

        if( (y() <= rocket->y()+25 && y() >= rocket->y()            // touch rocket
            && x()+30<= rocket->x()+35 && x()+30 >= rocket->x()-10) )
        {
            change_doodle=0;
            emit changeDoodle_signal();
            change_doodle=1;

            num_up=-100;
            for(int j=0; j<20; j++)
            {
                check_platform.at(unsigned(j))->distance = 400;
                check_platform.at(unsigned(j))->now_rocket = 1;
            }
            spring->now_rocket = 1;
            rocket->now_rocket = 1;
            monster->now_rocket = 1;
            blackhole->now_rocket = 1;
            protection_shield->now_rocket = 1;
            spring->distance = 400;
            rocket->distance = 400;
            monster->distance = 400;
            blackhole->distance = 400;
            protection_shield->distance = 400;
            rocket->setPixmap(QPixmap(""));
        }
        if( rocket->now_rocket==0 &&                            //touch shield
               y() <= protection_shield->y()+15 && y() >= protection_shield->y()
            && x()+30<= protection_shield->x()+33 && x()+30 >= protection_shield->x()-10)
        {
            have_protect=1;
            change_doodle=2;
            protection_shield->setPos(0, 0);
            emit changeDoodle_signal();
        }
    }
    else{
        dis=0;

        if(change_doodle==1)
            emit changeDoodle_signal();

        setPos(x(), y() + 2);

        for(int i=0; i<20; i++)
        {
            if( y()+60 <= spring->y()+10 && y()+60 >= spring->y()       //touch spring
                && x()+30<= spring->x()+30 && x()+30 >= spring->x()-10)
            {
                num_up=-50;
                for(int j=0; j<20; j++)
                    check_platform.at(unsigned(j))->distance = 300;
                spring->distance = 300;
                rocket->distance = 300;
                monster->distance = 300;
                blackhole->distance = 300;
                protection_shield->distance = 300;
                spring->setPixmap(QPixmap(":/res/spring.png").scaled(20, 40));
                spring->setPos(spring->x(), spring->y()-20);
                break;
            }
            if( y()+60 <= rocket->y()+12.5 && y()+60 >= rocket->y()     //touch rocket
                && x()+30<= rocket->x()+35 && x()+30 >= rocket->x()-10)
            {
                change_doodle=0;
                emit changeDoodle_signal();

                change_doodle=1;
                num_up=-100;
                for(int j=0; j<20; j++)
                {
                    check_platform.at(unsigned(j))->distance = 400;
                    check_platform.at(unsigned(j))->now_rocket = 1;
                }
                spring->now_rocket = 1;
                rocket->now_rocket = 1;
                monster->now_rocket = 1;
                blackhole->now_rocket = 1;
                protection_shield->now_rocket = 1;
                spring->distance = 400;
                rocket->distance = 400;
                monster->distance = 400;
                blackhole->distance = 400;
                protection_shield->distance = 400;
                rocket->setPixmap(QPixmap(""));
                break;
            }
            if( rocket->now_rocket==0 &&                //touch shield
                   y()+60 <= protection_shield->y()+10 && y()+60 >= protection_shield->y()
                && x()+30<= protection_shield->x()+33 && x()+30 >= protection_shield->x()-10)
            {
                have_protect=1;
                change_doodle=2;
                protection_shield->setPos(0, 0);
                emit changeDoodle_signal();
                break;
            }

            if((check_platform.at(unsigned(i))->platform_type==0 || check_platform.at(unsigned(i))->platform_type==2 ) &&
               y()+60 <= check_platform.at(unsigned(i))->y()+12 && y()+60 >= check_platform.at(unsigned(i))->y()+2
               && x()+30<=check_platform.at(unsigned(i))->x()+65 && x()+30>=check_platform.at(unsigned(i))->x()-10)
            {
                doodle_on_platform=1;
                dis=668-check_platform.at(unsigned(i))->y();

                if(dis>60)
                    num_up=100-static_cast<int>(dis/2.0);
                else if(dis<=60 && dis>0)
                    num_up=35;
                else
                    num_up=0;

                for(int j=0; j<20; j++)
                    check_platform.at(unsigned(j))->distance = dis;
                spring->distance = dis;
                rocket->distance = dis;
                monster->distance = dis;
                blackhole->distance = dis;
                protection_shield->distance = dis;
                break;
            }
        }
    }
    int platform_x, platform_y;
    while(check_platform.at(0)->set0 == 1)
    {
        emit add_score_signal();

        num_transparent_platform++;

        platform_x = static_cast<int>(static_cast<double>(rand()) /
                                      (RAND_MAX + 1.0) * (735.0 - 390.0) +390.0);
        platform_y = static_cast<int>(check_platform.at(unsigned(19))->y()) - static_cast<int>(static_cast<double>(rand()) /
                                                 (RAND_MAX + 1.0) * (53.0 -47.0) +47.0);
        check_platform.at(0)->setPos(platform_x,platform_y);
        check_platform.at(0)->set0=0;

        if(check_platform.at(0)->have_spring == 1)
        {
            spring->setPos(platform_x+12, platform_y-20);
            spring->setPixmap(QPixmap(":/res/spring_press.png").scaled(20, 20));
        }
        if(check_platform.at(0)->have_rocket == 1)
        {
            rocket->setPos(platform_x+30, platform_y-30);
            rocket->setPixmap(QPixmap(":/res/rocket.png").scaled(25, 30));
        }
        if(check_platform.at(0)->have_shield == 1)
        {
            protection_shield->setPos(platform_x+40, platform_y-23);
        }

        check_platform.push_back(check_platform.at(0));
        check_platform.erase(check_platform.begin());
    }

    if(monster->set0 == 1)
    {
        platform_x = static_cast<int>(static_cast<double>(rand()) /
                                      (RAND_MAX + 1.0) * (735.0 - 390.0) +390.0);
        platform_y = static_cast<int>(static_cast<double>(rand()) /
                                      (RAND_MAX + 1.0) * (-1000.0 +1200.0) -1200.0);
        monster->setPos(platform_x, platform_y);
        monster->set0=0;
    }

    if(blackhole->set0 == 1)
    {
        platform_x = static_cast<int>(static_cast<double>(rand()) /
                                      (RAND_MAX + 1.0) * (735.0 - 390.0) +390.0);
        platform_y = static_cast<int>(static_cast<double>(rand()) /
                                      (RAND_MAX + 1.0) * (-2000.0 +2500.0) -2500.0);
        blackhole->setPos(platform_x, platform_y);
        blackhole->set0=0;
    }

    if(check_platform.at(0)->now_rocket==0)
    {
        if(( y() > 720 )  ||
           ( ( ( y()+60 <= monster->y()+22 && y()+60 >= monster->y() )
             ||( y() <= monster->y()+22 && y() >= monster->y() ) )
             && x()+30 <= monster->x()+80 && x()+30 >= monster->x()-10)  ||
           ( ( ( y()+60 <= blackhole->y()+40 && y()+60 >= blackhole->y() )
               ||( y() <= blackhole->y()+40 && y() >= blackhole->y() ) )
             && x()+30 <= blackhole->x()+90 && x()+30 >= blackhole->x()-10 && have_protect!=1) )
        {
            gameover_add_score=1;

            change_doodle=3;
            emit changeDoodle_signal();

            game_over->setPixmap(QPixmap(":/res/gameover.png").scaled(300, 300));
            game_over->setPos(450,200);

            for(int i=0; i<20; i++)
            {
                check_platform.at(unsigned(i))->setPos(1000,0);
            }
            spring->setPos(1000,0);
            rocket->setPos(1000,0);
            protection_shield->setPos(1000,0);
            monster->setPos(1000,0);
            blackhole->setPos(1000,0);
        }
    }
}
