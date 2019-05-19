#ifndef PLAYER_H
#define PLAYER_H
#include<vector>
#include"Bullet.h"

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
    
    //guns' types
    enum Guns
    {
        pistol,
        cumgun,
        brutgun
    };
    int current_gun;
    
    int shooting_direction;
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

    void shoot(vector<Bullet*>& hero_bullets);
    void move(int direction);

    bool has_any_ammo();    
    void set_ammo(int ammo,string type);
    Ammo get_ammo();
    
    void set_health(int health);
    int get_health();
    
    void animate(int direction);
    
    void choose_new_gun(int gun_number);

private:
    // all guns have different speed, count of shoots, damage e.t.c
    void shoot_brutgun(vector<Bullet*>& hero_bullets,
                       GraphicalSettings& grsettings,
                       PhysicalSettings& psettings,
                       GameSettings& gsettings);
                       
    void shoot_pistol(vector<Bullet*>& hero_bullets,
                       GraphicalSettings& grsettings,
                       PhysicalSettings& psettings,
                       GameSettings& gsettings);
                       
    void shoot_cumgun(vector<Bullet*>& hero_bullets,
                       GraphicalSettings& grsettings,
                       PhysicalSettings& psettings,
                       GameSettings& gsettings);
};

#endif // PLAYER_H














