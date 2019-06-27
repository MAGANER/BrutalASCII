#ifndef SUICIDEBOY_H
#define SUICIDEBOY_H

#include"Monster.h"
/*
    >>> the most stupid
    >>> when collides hero causes damage to him
    >>> when he see hero he flies to the one direction with high speed
    >>> dies if collides any wall
*/

class SuicideBoy : public Monster
{
private:
    int attack_direction;
    void fly_to_target();
    bool collided_target(PhysicalSettings target_settings);
public:
    SuicideBoy(GraphicalSettings graph_settings,PhysicalSettings phys_settings, GameSettings game_settings);
    ~SuicideBoy();

    void go(vector<GameObject*>& walls);
    void search_target(Vector2f& target_pos);
    

};

#endif // SUICIDEBOY_H
