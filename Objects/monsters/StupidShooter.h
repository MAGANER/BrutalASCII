#ifndef STUPIDSHOOTER_H
#define STUPIDSHOOTER_H

#include <BaseShooterMonster.h>


/*
 >>don't avoid bullet
 >>don't see at comrades
 >>don't follow target
*/
class StupidShooter : public BaseShooterMonster
{
public:
    StupidShooter(GraphicalSettings graph_settings,
                  PhysicalSettings phys_settings,
                  GameSettings game_settings,
                  int visible_radius);
    ~StupidShooter();
    
    void avoid_bullet(vector<Bullet*> & hero_bullets, bool& able_to_go);
    void follow_target();


};

#endif // STUPIDSHOOTER_H
