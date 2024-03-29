#ifndef BULLET_H
#define BULLET_H

#include"GameObject.h"
#include"Physics/Direction.h"
/*
 all bullets in game have 2 differences: damage and speed
 so all of them can be objects of this class.
 
 this class is common for all bullets.
*/
class Bullet : public GameObject
{
protected:
    int damage;
    int direction;
public:
    Bullet(GraphicalSettings graph_settings,
           PhysicalSettings phys_settings,
           GameSettings game_settings,
           int damage);
    virtual ~Bullet();
    
    void set_direction(int new_direction);
    int get_direction();
    int get_damage();
    virtual void move();
};

#endif // BULLET_H
