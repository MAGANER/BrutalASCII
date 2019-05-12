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
    if(direction == Direction::left)
    {
        gobject_spr.move(-0.6f,0.0f);
    }
    if(direction == Direction::right)
    {
        gobject_spr.move(0.6f,0.0f);
    }
    update_position(get_position());
}
void Bullet::set_direction(int new_direction)
{
    direction = new_direction;
}