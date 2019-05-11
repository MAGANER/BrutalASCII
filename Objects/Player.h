#ifndef PLAYER_H
#define PLAYER_H

#include <GameObject.h>


class Player : public GameObject
{
private:
        
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


};

#endif // PLAYER_H
