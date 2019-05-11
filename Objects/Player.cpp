#include "Player.h"

Player::Player(GraphicalSettings graph_settings,
               PhysicalSettings phys_settings,
                GameSettings game_settings):GameObject(graph_settings,phys_settings,game_settings)
{
    health = 10;
    ammo.brutgun = 0;
    ammo.cumgun = 0;
    ammo.pistol = 0;
}

Player::~Player()
{

}

void Player::move(int direction,float delta_time)
{
    update_position(get_position());
    switch(direction)
    {
    case Direction::left:
        gobject_spr.move(-0.2f,0.0f);
        break;
    case Direction::right:
        gobject_spr.move(0.2f,0.0f);
        break;
    case Direction::up:
        gobject_spr.move(0.0f,-0.2f);
        break;
    case Direction::down:
        gobject_spr.move(0.0f,0.2f);
        break;
    }
}
int Player::get_health()
{
    return health;
}
void Player::set_health(int health)
{
    this->health = health;
}
Ammo Player::get_ammo()
{
    return ammo;
}
void Player::set_ammo(int ammo, string type)
{
    if(type == "pistol")
    {
        this->ammo.pistol += ammo;
    }
    if(type == "cumgun")
    {
        this->ammo.cumgun += ammo;
    }
    if(type == "brutgun")
    {
        this->ammo.brutgun += ammo;
    }
}



