#include "Bullet.h"

Bullet::Bullet(GraphicalSettings graph_settings,
               PhysicalSettings phys_settings, 
               GameSettings game_settings,
               int damage)
	          :GameObject(graph_settings,phys_settings,game_settings)
{
    this->damage = damage;
}

Bullet::~Bullet()
{
}


int Bullet::get_damage()
{
    return damage;
}
void Bullet::move()
{
    update_position(get_position()); // update position of physical body
     
    if(direction == Direction::left)
    {
        gobject_spr.move(-speed.x,speed.y);
    }
    if(direction == Direction::right)
    {
        gobject_spr.move(speed.x,speed.y);
    }
    if(direction == Direction::down)
    {
        gobject_spr.move(speed.x,speed.y);
    }
    if(direction == Direction::up)
    {
        gobject_spr.move(speed.x,-speed.y);
    }
   
}
void Bullet::set_direction(int new_direction)
{
    direction = new_direction;
}