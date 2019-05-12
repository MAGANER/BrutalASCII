#ifndef BULLET_H
#define BULLET_H

#include <GameObject.h>


class Bullet : public GameObject
{
private:
    int damage;
    int direction;
public:
    enum Direction
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
