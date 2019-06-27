#ifndef PLAYER_H
#define PLAYER_H
#include<vector>
#include"MadBullet.h" // also it includes base class Bullet
#include"Physics/Direction.h"


// counter of ammo
struct Ammo
{
    int pistol;
    int cumgun;
    int brutgun;
    int doublegun;
    int madgun;
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
        brutgun,
        doublegun,
        madgun
    };
    int current_gun;
    
    int shooting_direction; // direction of bullet
    int moving_direction;
    int animation_direction; // left of right
    
    bool key_is_pressed;
    int keys;
public:
    Player(GraphicalSettings graph_settings,PhysicalSettings phys_settings, GameSettings game_settings);
    ~Player();

    void shoot(vector<Bullet*>& hero_bullets);
    void move(int direction);
    int get_direction();
    void set_direction(int value);
    
    bool has_any_ammo();    
    void set_ammo(int ammo,string type);
    void destroy_ammo(); // when hero dies
    Ammo get_ammo();
    void choose_new_gun(int gun_number);
        
    void set_health(int health);
    int get_health();
    
    void set_keys(int number);
    int get_keys();
    
    void animate();

    
    void check_key_pressing(vector<Bullet*>& hero_bullets);

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
                       
    void shoot_doublegun(vector<Bullet*>& hero_bullets,
                          GraphicalSettings& grsettings,
                          PhysicalSettings& psettings,
                          GameSettings& gsettings);
                          
    void shoot_madgun(vector<Bullet*>& hero_bullets,
                       GraphicalSettings& grsettings,
                       PhysicalSettings& psettings,
                       GameSettings& gsettings);
};

#endif // PLAYER_H














