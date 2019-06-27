#include "SuicideBoy.h"

SuicideBoy::SuicideBoy(GraphicalSettings graph_settings,
                       PhysicalSettings phys_settings,
                       GameSettings game_settings):
                           Monster(graph_settings,phys_settings,game_settings)
{
    attack_direction = -1;
}

SuicideBoy::~SuicideBoy()
{
}

void SuicideBoy::go(vector<GameObject*>& walls)
{
    bool collision =  Monster::check_collided_walls(walls);
    if(!collision)
    {
        switch(direction)
        {
        case Direction::down:
            gobject_spr.move(0.0f,-speed.y);
            break;
        case Direction::left:
            gobject_spr.move(-speed.x,0.0f);
            break;
        case Direction::right:
            gobject_spr.move(speed.x,0.0f);
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
            break;
        case Direction::right:
            direction = Direction::left;
            break;
        case Direction::up:
            direction = Direction::down;
            break;
        } 
        collision = false;
    }
}
void SuicideBoy::search_target(Vector2f& target_pos)
{
    
}





















