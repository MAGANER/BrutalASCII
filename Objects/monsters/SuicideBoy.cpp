#include "SuicideBoy.h"

SuicideBoy::SuicideBoy(GraphicalSettings graph_settings,
                       PhysicalSettings phys_settings,
                       GameSettings game_settings):
                           Monster(graph_settings,phys_settings,game_settings)
{
    health = 1;
}

SuicideBoy::~SuicideBoy()
{
}

void SuicideBoy::search_target(Vector2f target_pos)
{
    bool is_on_the_same_line_OX = target_pos.x == get_position().x ||
                                  (target_pos.x+64.0f > get_position().x &&
                                   target_pos.x+64.0f < get_position().x + 64.0f);
    

    bool is_under = mod(target_pos.y) < mod(get_position().y);
    
    //SEARCH TARGET ONLY ONE TIME 
    //WHEN HE FINDS, HE JUST FLIES AS MADMAN
    
    if(is_under && is_on_the_same_line_OX && !see_target)
    {
        see_target = true;
        direction = Direction::up;
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
    speed = Vector2f(0.0f,-12.0f);
}




















