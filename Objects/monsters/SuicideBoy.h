#ifndef SUICIDEBOY_H
#define SUICIDEBOY_H

#include <Monster.h>
/*
    >>> the most stupid
    >>> when collides hero causes damage to him
    >>> when he see hero he flies to the one direction with high speed
    >>> dies if collides any wall
*/

class SuicideBoy : public Monster
{
public:
    SuicideBoy(GraphicalSettings graph_settings,PhysicalSettings phys_settings, GameSettings game_settings);
    ~SuicideBoy();



};

#endif // SUICIDEBOY_H
