#include "Monster.h"

Monster::Monster(GraphicalSettings graph_settings,
                 PhysicalSettings phys_settings,
                 GameSettings game_settings):GameObject(graph_settings,phys_settings,game_settings)
{
    direction = generate_direction();
    see_target = false;
    

}

Monster::~Monster()
{
}


bool Monster::is_dead()
{
    // return true, if is dead
    if(health <= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int Monster::generate_direction()
{
    if(get_type() == "sboy")
    {
         return Direction::left + rand() % Direction::down;
    }
    else
    {
         return Direction::left + rand() % Direction::right;
    }
   
}

int Monster::get_direction()
{
    return direction;
}
void Monster::go(bool ability_to_go)
{
    update_position(get_position()); // update position of physical body
    if(!ability_to_go)
    {
        switch(direction)
        {
        case Direction::down:
            gobject_spr.move(0.0f,-speed.y);
            break;
        case Direction::left:
            gobject_spr.move(-speed.x,0.0f);
            looking_direction = Direction::left;
            break;
        case Direction::right:
            gobject_spr.move(speed.x,0.0f);
            looking_direction = Direction::right;
            break;
        case Direction::up:
            gobject_spr.move(0.0f,speed.y);
            break;
        }
    }
    else
    {
        switch(direction)
        {
        case Direction::down:
            direction = Direction::up;
            break;
        case Direction::left:
            direction = Direction::right;
            looking_direction = Direction::left;
            break;
        case Direction::right:
            direction = Direction::left;
            looking_direction = Direction::right;
            break;
        case Direction::up:
            direction = Direction::down;
            break;
        }
        ability_to_go = false; 
    }
}
void Monster::set_health(int value)
{
    health = value;
}
int Monster::get_health()
{
    return health;
}
int Monster::get_damage()
{
    return damage;
}
bool Monster::does_see_target()
{
    return see_target;
}
void Monster::set_direction(int new_one)
{
    direction = new_one;
}
