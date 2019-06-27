#ifndef TURRELL_H
#define TURRELL_H
#include"Timer.h"
#include"Physics/Direction.h"
#include"bullets/Bullet.h"

/*
 this object always has static position
 it can be destroyed, also it shoots and bullet
 can kill anyone:monster or hero, doesn't matter
*/
class Turrell : public GameObject
{
private:
    Timer * timer;
    float time_to_shoot;
    
    int shooting_direction;
public:
    Turrell(GraphicalSettings graph_settings,
            PhysicalSettings phys_settings,
            GameSettings game_settings,
            int shooting_direction);
    ~Turrell();
    
    void shoot(vector<Bullet*>& turrells_bullets);


};

#endif // TURRELL_H
