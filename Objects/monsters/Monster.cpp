#include "Monster.h"

Monster::Monster(GraphicalSettings graph_settings,
                 PhysicalSettings phys_settings,
                 GameSettings game_settings):GameObject(graph_settings,phys_settings,game_settings)
{
    direction = generate_direction();
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
bool Monster::check_collided_walls(vector<GameObject*>& walls)
{
    for(size_t i = 0;i<walls.size();++i)
    {
        bool collision = collision_checker.object_collides((this),walls[i]);
        if(collision)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
int Monster::generate_direction()
{
    srand(time(0));
    return Direction::left + rand() % Direction::down;
}










