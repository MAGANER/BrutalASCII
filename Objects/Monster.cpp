#include "Monster.h"

Monster::Monster(GraphicalSettings graph_settings,
                 PhysicalSettings phys_settings,
                 GameSettings game_settings):GameObject(graph_settings,phys_settings,game_settings)
{
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