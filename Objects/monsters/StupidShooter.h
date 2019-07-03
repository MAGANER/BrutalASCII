#ifndef STUPIDSHOOTER_H
#define STUPIDSHOOTER_H

#include <BaseShooterMonster.h>


/*
 >>don't avoid bullet
 >>don't see at comrades
*/
class StupidShooter : public BaseShooterMonster
{
public:
    StupidShooter(GraphicalSettings graph_settings,
                  PhysicalSettings phys_settings,
                  GameSettings game_settings,
                  int visible_radius);
    ~StupidShooter();
    
    void avoid_bullet();
    void follow_target();


};

#endif // STUPIDSHOOTER_H
