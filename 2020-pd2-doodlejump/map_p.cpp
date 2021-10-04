#include "map_p.h"

map_p::map_p():
    distance(0),
    platform_type(0),
    have_spring(0),
    have_rocket(0),
    have_shield(0),
    now_rocket(0)
{

}

void map_p::roll()
{
    if(distance>0)
    {
        if(!now_rocket)
        {
            setPos(x(), y() + 2);
            distance=distance-2;
        }
        else
        {
            setPos(x(), y() + 4);
            distance=distance-2;
        }
    }
    if(distance<=0)
        now_rocket=0;
    if(y() > 720)
        set0=1;
}

platform2::platform2():
    move_to_right(0)
{

}

void platform2::roll()      //move platform
{
    if(move_to_right <= 100)
    {
        setPos(x()+0.7, y());
        move_to_right++;
    }
    else if(move_to_right > 100 && move_to_right <= 200)
    {
        setPos(x()-0.7, y());
        move_to_right++;
    }
    else
        move_to_right=0;

    if(distance>0)
    {
        if(!now_rocket)
        {
            setPos(x(), y() + 2);
            distance=distance-2;
        }
        else
        {
            setPos(x(), y() + 4);
            distance=distance-2;
        }
    }
    if(distance<=0)
        now_rocket=0;
    if(y() > 720)
        set0=1;
}
