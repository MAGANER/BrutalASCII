#ifndef MADBULLET_H
#define MADBULLET_H
#include <Bullet.h>


class MadBullet : public Bullet
{
private:
    void generate_damage();
    void generate_speed();
public:
    MadBullet(GraphicalSettings graph_settings,
              PhysicalSettings phys_settings,
              GameSettings game_settings,
              int damage);
    ~MadBullet();
    
    void move();


};

#endif // MADBULLET_H
