#include "StupidShooter.h"

StupidShooter::StupidShooter(GraphicalSettings graph_settings,
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

StupidShooter::~StupidShooter()
{
}

void StupidShooter::avoid_bullet(vector<Bullet*> & hero_bullets, bool& able_to_go)
{
    //do nothing
}
void StupidShooter::follow_target()
{
    //do nothing
}






















