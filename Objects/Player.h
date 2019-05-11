#ifndef PLAYER_H
#define PLAYER_H

#include <GameObject.h>

struct Ammo
{
    int pistol;
    int cumgun;
    int brutgun;
};
class Player : public GameObject
{
private:
    int health;
    Ammo ammo;
public:
    enum Direction
    {
        left,
        right,
        up,
        down
    };
    Player(GraphicalSettings graph_settings,PhysicalSettings phys_settings, GameSettings game_settings);
    ~Player();

    void shoot();
    void move(int direction,float delta_time);
    
    void set_ammo(int ammo,string type);
    Ammo get_ammo();
    
    void set_health(int health);
    int get_health();


};

#endif // PLAYER_H














