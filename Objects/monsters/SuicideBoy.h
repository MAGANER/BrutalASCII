#ifndef SUICIDEBOY_H
#define SUICIDEBOY_H

#include"Monster.h"
/*
    >>> the most stupid
    >>> when collides hero causes damage to him
    >>> when he see hero he flies to the one direction with high speed
    >>> dies if collides any wall
    >>  see hero only under/below itself
*/

class SuicideBoy : public Monster
{
private:
    void fly_to_target();
    bool collided_target(PhysicalSettings target_settings);
public:
    SuicideBoy(GraphicalSettings graph_settings,PhysicalSettings phys_settings, GameSettings game_settings);
    ~SuicideBoy();
    
    void search_target(Vector2f target_pos);
    void attack();

};

#endif // SUICIDEBOY_H
