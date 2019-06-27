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

void SuicideBoy::search_target(Vector2f target_pos)
{
    bool is_on_the_same_line_OX = target_pos.x == get_position().x ||
                                  (target_pos.x+64.0f > get_position().x &&
                                   target_pos.x+64.0f < get_position().x + 64.0f);
    

    
    bool is_below = target_pos.y+64.0f < get_position().y;
    bool is_under = target_pos.y > get_position().y;
    
    if(is_below && is_on_the_same_line_OX)
    {
        see_target = true;
        attack_direction = Direction::up;
    }
    else if(is_under && is_on_the_same_line_OX)
    {
        see_target = true;
        attack_direction = Direction::down;
    }
    else
    {
        see_target = false;
    }
}
void SuicideBoy::attack()
{
    if(see_target)
    {
        fly_to_target();
    }
}
void SuicideBoy::fly_to_target()
{
    speed = Vector2f(10.0f,10.0f);
    cout<<"ass"<<endl;
    
}




















