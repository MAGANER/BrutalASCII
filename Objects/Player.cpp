#include "Player.h"

Player::Player(GraphicalSettings graph_settings,
               PhysicalSettings phys_settings,
                GameSettings game_settings):GameObject(graph_settings,phys_settings,game_settings)
{

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