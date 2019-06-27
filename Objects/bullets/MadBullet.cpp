#include "MadBullet.h"

MadBullet::MadBullet(GraphicalSettings graph_settings,
                     PhysicalSettings phys_settings,
                     GameSettings game_settings,
                     int damage):Bullet(graph_settings,phys_settings,game_settings,damage)
{
    srand(time(0));
    generate_damage();
}

MadBullet::~MadBullet()
{

}

void MadBullet::move()
{
    update_position(get_position()); // update position of physical body
    srand(time(0));
    generate_speed();
    if(direction == Direction::left)
    {
        gobject_spr.move(-speed.x,speed.y);
    }
    if(direction == Direction::right)
    {
        gobject_spr.move(speed.x,speed.y);
    }
}
void MadBullet::generate_damage()
{
    damage = 1 + rand() % 5;
}
void MadBullet::generate_speed()
{
    float x =(float) 10 + rand() % 20;
    float y =(float) (-7) + rand() % 7;
    speed.x = x;
    speed.y = y;
}





