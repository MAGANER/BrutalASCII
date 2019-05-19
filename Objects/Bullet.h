#ifndef BULLET_H
#define BULLET_H

#include <GameObject.h>

/*
 all bullets in game have 2 differences: damage and speed
 so all of them can be objects of this class.
 
 this class is common for all bullets.
*/
class Bullet : public GameObject
{
private:
    int damage;
    int direction;
public:
    enum Direction // of moving
    {
        left,
        right
    };
    
    Bullet(GraphicalSettings graph_settings,
           PhysicalSettings phys_settings,
           GameSettings game_settings,
           int damage);
    ~Bullet();
    
    void set_direction(int new_direction);
    int get_damage();
    void move();
};

#endif // BULLET_H
