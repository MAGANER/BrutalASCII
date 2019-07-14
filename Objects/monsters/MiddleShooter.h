#ifndef MIDDLESHOOTER_H
#define MIDDLESHOOTER_H

#include <BaseShooterMonster.h>

/*
 >>avoid bullet
 >>follow target
 >>don't see at comrades
*/

class MiddleShooter : public BaseShooterMonster
{
public:
    MiddleShooter(GraphicalSettings graph_settings,
                  PhysicalSettings phys_settings,
                  GameSettings game_settings,
                  int visible_radius);
    ~MiddleShooter();
    
    void avoid_bullet(vector<Bullet*> & hero_bullets, bool& able_to_go);
    void follow_target();
};

#endif // MIDDLESHOOTER_H
