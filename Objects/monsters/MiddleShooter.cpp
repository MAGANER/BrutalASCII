#include "MiddleShooter.h"

MiddleShooter::MiddleShooter(GraphicalSettings graph_settings,
                             PhysicalSettings phys_settings,
                             GameSettings game_settings,
                             int visible_radius):
                                 BaseShooterMonster(graph_settings,
                                                    phys_settings,
                                                    game_settings,
                                                    visible_radius)
{
    health = 2;
}

MiddleShooter::~MiddleShooter()
{

}

void MiddleShooter::avoid_bullet(vector<Bullet*>& hero_bullets, bool& able_to_go)
{
    bool near_bullet = is_bullet_near(hero_bullets);
    
    srand(time(0));
    if(near_bullet && !try_to_avoid_bullet)
    {
        //generate direction up or down
        avoiding_direction = Direction::up + rand() % Direction::down;
        try_to_avoid_bullet = true;
        
        if(!pos_taken)
        {
            pos_before_running = get_position();
            pos_taken = true;
        }
    }
        
    if(try_to_avoid_bullet)
    {
        run_in_fear(avoiding_direction,able_to_go);
    }


}
void MiddleShooter::follow_target()
{
    
}









